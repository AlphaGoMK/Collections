#!/usr/bin/env python3
"""
将目录下的 .hpp 文件中的类内联方法定义拆分为 .hpp 声明 + .cpp 实现。

用法:
    python split_hpp_cpp.py /path/to/headers [--in-place]

默认行为：
- 读取 *.hpp
- 生成同名 *.cpp（若已存在会被覆盖）
- 仅当检测到可拆分的方法定义时，才会更新对应 hpp

说明：
- 支持一个 hpp 中多个 class。
- 支持类继承写法（不会影响实现生成）。
- 支持构造/析构、普通成员函数、const/noexcept/override/final 等尾部限定。
- 跳过宏定义、friend、template 方法、operator 重载（可按需扩展）。
"""

from __future__ import annotations

import argparse
import re
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional, Tuple


ACCESS_SPEC = {"public", "protected", "private"}


@dataclass
class MethodChunk:
    class_name: str
    header: str
    body: str
    indent: str


@dataclass
class Replacement:
    start: int
    end: int
    text: str


CLASS_RE = re.compile(r"\bclass\s+([A-Za-z_]\w*)\b")


def strip_comments_and_strings(src: str) -> str:
    """返回等长字符串，将注释/字符串替换为空格，便于做 brace/keyword 扫描。"""
    out = list(src)
    i = 0
    n = len(src)
    while i < n:
        ch = src[i]
        nxt = src[i + 1] if i + 1 < n else ""

        # line comment
        if ch == "/" and nxt == "/":
            out[i] = out[i + 1] = " "
            i += 2
            while i < n and src[i] != "\n":
                out[i] = " "
                i += 1
            continue

        # block comment
        if ch == "/" and nxt == "*":
            out[i] = out[i + 1] = " "
            i += 2
            while i + 1 < n and not (src[i] == "*" and src[i + 1] == "/"):
                out[i] = " "
                i += 1
            if i + 1 < n:
                out[i] = out[i + 1] = " "
                i += 2
            continue

        # raw string R"...(...)..."
        if ch == "R" and nxt == '"':
            start = i
            i += 2
            delim = []
            while i < n and src[i] != "(":
                delim.append(src[i])
                i += 1
            if i >= n:
                i = start + 1
                continue
            closing = ")" + "".join(delim) + '"'
            i += 1
            while i + len(closing) <= n and src[i : i + len(closing)] != closing:
                i += 1
            end = min(n, i + len(closing))
            for k in range(start, end):
                out[k] = " "
            i = end
            continue

        # normal string / char
        if ch in ('"', "'"):
            quote = ch
            start = i
            i += 1
            while i < n:
                if src[i] == "\\":
                    i += 2
                    continue
                if src[i] == quote:
                    i += 1
                    break
                i += 1
            for k in range(start, min(i, n)):
                out[k] = " "
            continue

        i += 1

    return "".join(out)


def find_matching(src: str, pos: int, left: str, right: str) -> int:
    """src[pos] == left，返回匹配 right 的位置，找不到返回 -1。"""
    if pos < 0 or pos >= len(src) or src[pos] != left:
        return -1
    depth = 1
    i = pos + 1
    while i < len(src):
        if src[i] == left:
            depth += 1
        elif src[i] == right:
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def find_classes(src: str, sanitized: str) -> List[Tuple[str, int, int]]:
    """返回 [(class_name, body_start, body_end), ...]，body 范围不含外层 {}。"""
    classes: List[Tuple[str, int, int]] = []
    for m in CLASS_RE.finditer(sanitized):
        cls = m.group(1)
        brace_pos = sanitized.find("{", m.end())
        if brace_pos == -1:
            continue
        # 排除前向声明 class A;
        semi = sanitized.find(";", m.end(), brace_pos)
        if semi != -1:
            continue
        end = find_matching(sanitized, brace_pos, "{", "}")
        if end == -1:
            continue
        classes.append((cls, brace_pos + 1, end))
    return classes


def last_non_space(text: str, idx: int) -> int:
    i = idx
    while i >= 0 and text[i].isspace():
        i -= 1
    return i


def first_non_space(text: str, idx: int) -> int:
    i = idx
    n = len(text)
    while i < n and text[i].isspace():
        i += 1
    return i


def should_skip_method_header(header: str) -> bool:
    h = header.strip()
    if not h:
        return True
    if h.startswith("template"):
        return True
    if " friend " in f" {h} " or h.startswith("friend "):
        return True
    if "operator" in h:
        return True
    return False


def normalize_header(header: str) -> str:
    h = header.strip()
    # 去掉可能误吸收的访问控制前缀，例如 "public:"
    h = re.sub(r"^(?:public|protected|private)\s*:\s*", "", h, flags=re.S)
    # 去掉类内才有意义的 virtual 关键字
    h = re.sub(r"^virtual\s+", "", h)
    return h.strip()


def transform_header_to_declaration(header: str) -> str:
    h = normalize_header(header).rstrip()
    if h.endswith(";"):
        return h
    return h + ";"


def make_out_of_class_signature(class_name: str, header: str) -> str:
    """
    将类内函数头改成类外定义头。
    例：
      void f(int) const -> void Class::f(int) const
      MyClass() noexcept -> MyClass::MyClass() noexcept
      ~MyClass() -> MyClass::~MyClass()
    """
    h = " ".join(normalize_header(header).split())

    # 在第一个 '(' 之前提取函数名 token。
    p = h.find("(")
    if p == -1:
        return h
    pre = h[:p].rstrip()

    # 去掉末尾可能的 requires（简单场景先不支持复杂 requires）
    if pre.endswith("requires"):
        return h

    m = re.search(r"([~A-Za-z_]\w*)\s*$", pre)
    if not m:
        return h
    name = m.group(1)
    name_start = m.start(1)
    pre2 = pre[:name_start] + f"{class_name}::{name}"
    return pre2 + h[p:]


def extract_methods_from_class(
    src: str, sanitized: str, class_name: str, body_start: int, body_end: int
) -> Tuple[List[MethodChunk], List[Replacement]]:
    methods: List[MethodChunk] = []
    replacements: List[Replacement] = []

    i = body_start
    segment = sanitized[body_start:body_end]

    # 记录类内层级，确保仅提取第一层成员（不进入函数体/lambda 里继续识别）
    depth = 0
    last_stmt_start = body_start

    while i < body_end:
        ch = sanitized[i]
        if ch == "{":
            if depth == 0:
                # 候选函数体起点
                # 找到该语句头部范围 [stmt_start, i)
                stmt_end = i
                stmt_start = last_stmt_start
                stmt = src[stmt_start:stmt_end]
                stmt_s = sanitized[stmt_start:stmt_end]

                # header 至少包含 ')'
                if ")" in stmt_s:
                    header = stmt.strip()
                    # 排除 access label: public:
                    if not re.match(r"^(public|protected|private)\s*:\s*$", header):
                        # 排除控制语句 / 宏 等
                        lowered = header.lstrip()
                        if not re.match(r"^(if|for|while|switch|catch)\b", lowered):
                            if not should_skip_method_header(header):
                                close = find_matching(sanitized, i, "{", "}")
                                if close != -1 and close <= body_end:
                                    # 替换函数体为分号，保持原 header/缩进 不变
                                    rep_start = i
                                    rep_end = close + 1

                                    # 缩进取 header 第一行前导空白
                                    first_line = src[stmt_start:stmt_end].splitlines()[0]
                                    indent = re.match(r"\s*", first_line).group(0)

                                    body = src[i : close + 1]
                                    methods.append(
                                        MethodChunk(
                                            class_name=class_name,
                                            header=header,
                                            body=body,
                                            indent=indent,
                                        )
                                    )
                                    replacements.append(
                                        Replacement(start=rep_start, end=rep_end, text=";")
                                    )
                                    i = rep_end
                                    continue
            depth += 1
        elif ch == "}":
            depth = max(0, depth - 1)
            if depth == 0:
                # 语句结束，更新 last_stmt_start 到下一个 token
                j = i + 1
                while j < body_end and src[j].isspace():
                    j += 1
                if j < body_end and src[j] == ";":
                    j += 1
                last_stmt_start = j
        elif ch == ";" and depth == 0:
            last_stmt_start = i + 1

        i += 1

    return methods, replacements


def apply_replacements(text: str, replacements: List[Replacement]) -> str:
    if not replacements:
        return text
    replacements = sorted(replacements, key=lambda x: x.start)
    out: List[str] = []
    cursor = 0
    for rep in replacements:
        if rep.start < cursor:
            # 重叠替换，跳过
            continue
        out.append(text[cursor : rep.start])
        out.append(rep.text)
        cursor = rep.end
    out.append(text[cursor:])
    return "".join(out)


def build_cpp_content(hpp_path: Path, methods: List[MethodChunk]) -> str:
    include_name = hpp_path.name
    lines = [f'#include "{include_name}"', ""]

    for idx, m in enumerate(methods):
        signature = make_out_of_class_signature(m.class_name, m.header)
        lines.append(signature)
        lines.append(m.body)
        if idx != len(methods) - 1:
            lines.append("")

    lines.append("")
    return "\n".join(lines)


def process_hpp(hpp_path: Path, in_place: bool = True) -> Tuple[bool, Optional[Path]]:
    original = hpp_path.read_text(encoding="utf-8")
    sanitized = strip_comments_and_strings(original)

    all_methods: List[MethodChunk] = []
    all_replacements: List[Replacement] = []

    for class_name, body_start, body_end in find_classes(original, sanitized):
        methods, reps = extract_methods_from_class(
            original, sanitized, class_name, body_start, body_end
        )
        all_methods.extend(methods)
        all_replacements.extend(reps)

    if not all_methods:
        return False, None

    updated_hpp = apply_replacements(original, all_replacements)
    cpp_content = build_cpp_content(hpp_path, all_methods)

    cpp_path = hpp_path.with_suffix(".cpp")
    cpp_path.write_text(cpp_content, encoding="utf-8")

    if in_place:
        hpp_path.write_text(updated_hpp, encoding="utf-8")

    return True, cpp_path


def main() -> int:
    parser = argparse.ArgumentParser(description="批量拆分 hpp 内联定义到 cpp")
    parser.add_argument("directory", type=Path, help="待处理目录")
    parser.add_argument(
        "--no-in-place",
        action="store_true",
        help="不回写 hpp（只生成 cpp）",
    )
    args = parser.parse_args()

    root = args.directory
    if not root.exists() or not root.is_dir():
        raise SystemExit(f"目录不存在或不是目录: {root}")

    hpp_files = sorted(root.rglob("*.hpp"))
    if not hpp_files:
        print("未找到 .hpp 文件。")
        return 0

    changed = 0
    for hpp in hpp_files:
        ok, cpp_path = process_hpp(hpp, in_place=not args.no_in_place)
        if ok:
            changed += 1
            print(f"[OK] {hpp} -> {cpp_path}")
        else:
            print(f"[SKIP] {hpp} (未检测到可拆分方法)")

    print(f"完成，处理文件数: {changed}/{len(hpp_files)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
