# Object Detection

## mAP

> AP is averaged over all categories. Traditionally, this is called “mean average precision” (mAP). We make no distinction between AP and mAP (and likewise AR and mAR) and assume the difference is clear from context.  

[mAP (mean Average Precision) for Object Detection - Jonathan Hui - Medium](https://medium.com/@jonathan_hui/map-mean-average-precision-for-object-detection-45c121a31173)

---

## CornerNet

> anchor-free

#### Motivation

1. anchor box太多，只有少部分和GT重合
2. anchor 选择需要人为设计（数量，尺寸，比例），不同尺度anchor设置不同

两个部分： 1) 检测角网络，左上+右下 2) 嵌入网络，用于匹配角点

#### Method

![](Figures/1e682da0e78dfe82e953f541d1580f86f14af8f6.png)

**检测corner网络**：提特征之后，经过corner pooling产生每个类别的左上角和右下角的heat map。为正负样本匹配，只惩罚GT一定范围外的预测点（通过IoU threshold限制radius）
**计算嵌入embed网络**：用于匹配同框的左上右下。损失函数：同框左上和右下接近（variance小），不同框的平均embed距离大。
<u>**Corner pooling** </u>：解决角点特征少，取一条线上的最大值pooling
![](Figures/63eebde8b0adc4b30eacb0eb14e2b291b78b0e87.png)
*Hourglass network*：提特征

**two stage得到预测框之后采用RoI pooling/align提取检测框内部的信息，只有内部信息(approx.)的特征再进行一次框定和分类（refine步骤）；而一阶段的方法在提取到特征之后分成两支进行框定和分类，没有对近似的只包含框内物体的特征(局部特征)进行再一次提取，所以精度较差**

-----

## CenterNet

> anchor-free

#### Motivation

CornerNet只用到边缘的特征信息，没有用到内部的特征信息（造成不止对物体的边缘敏感，也对背景的边缘敏感）。内部信息对于决定两个keypoint是否是同一个框有帮助。
CenterNet预测三元组：左上，右下，中心

#### Method

![](Figures/d9ab741df8f3e313182e9e5f3f47cc6d89eba5c4.png)
二分支：产生corner点并match形成框；产生center点。如果center点在框的central region，计算框，否则删除
<u>**central region**</u> 确定判定的中心区域的大小：大框偏小，小框偏大，整体线性

$\left\{\begin{array}{l}
{\operatorname{ctl}_{\mathrm{x}}=\frac{(n+1) \mathrm{tl}_{\mathrm{x}}+(n-1) \mathrm{br}_{\mathrm{x}}}{2 n}} \\
{\operatorname{ctl}_{\mathrm{y}}=\frac{(n+1) \mathrm{tl}_{\mathrm{y}}+(n-1) \mathrm{br}_{\mathrm{y}}}{2 n}} \\
{\operatorname{cbr}_{\mathrm{x}}=\frac{(n-1) \mathrm{tl}_{\mathrm{x}}+(n+1) \mathrm{br}_{\mathrm{x}}}{2 n}} \\
{\operatorname{cbr}_{\mathrm{y}}=\frac{(n-1) \mathrm{tl}_{\mathrm{y}}+(n+1) \mathrm{br}_{\mathrm{y}}}{2 n}}
\end{array}\right.$
N离散变化，过threshold后变系数n。小$\to$threshold$\to$大，3$\to$5

#### Enrich center&corner information

<u>**center pooling**</u> 用在预测中心点时，增加中心点的recognizable特征

```
例如找leftmost的（即把horizontal最大值传到最左边），每个点看自己到最右边的最大值，不断传，到最左可获得整条横线最大；找topmost（把vertical最大值传到最上面），每个点看自己到最下，不断传，到最上则可获得整条线最大
```

模块&示意图
![](Figures/ade09a091bb57b300358c745de23118416db2913.png)
![](Figures/ca0373639965a7c36e025eeef214af59716f68eb.png)

输出map表示是否为center点，然后找横向和纵向最大值

<u>**cascade corner pooling**</u> 增加角点的特征，相比corner pooling增加内部，使其不对边缘敏感
沿着边缘找边缘最大值，再从边缘最大值的位置 *向内找内部最大值* ，最后两个最大值相加
模块&示意图
![](Figures/cc6e39c86f14d245507fb1c4c2f691d87dc5a3c7.png)![](Figures/caa1d357e9dd10d63c81d52dcd69b0d045d9b9a3.png)

> Q: how to classification?  
> Need RoI align?  

---

## FCOS: Fully Convolutional One-Stage Object Detection

> anchor-free 消除anchor，减少IoU的计算和GT框的匹配。可以代替二阶段的RPN

按照像素进行预测<u>**per-pixel prediction**</u>，预测每一个像素点的四个维度的框 `(Left, Top, Right, Bottom)`👇
![](Figures/433cf8512698164d44e845d1d67fcaf628708061.png)

* 对于特征图上每一个点，对应一个原图上的框。直接把特征图上的像素点看成训练样本而不是在点上铺不同长宽比和大小的anchor框

* 对于一个点落在多个GT框中（ambiguous samples）选择最小的bbox作为target。同时通过multi-level prediction来减少数量。👇
  ![](Figures/376354c1dd3cfbe7facc6debbe8335f845c44e19.png)👆which bbox this location should regress？

* FCOS可以利用尽可能多的样本（特征图上的点形成的框）而不只是IoU足够大的anchor 来进行训练。每个点都去学习对框的预测，多个点共同产生多个类似的框，然后NMS选择最大的

* 对于ambiguous samples，采用多尺度特征图，每层限制4D vec中最大值的大小（<u>**限制每层特征图产生的bbox的大小**</u>），满足$m_i < \max(l,t,r,b) < m_{i+1}$。对于同一个点上多个框，因限制，所以在不同尺度特征图上构成的框进行regress，一个feature map上一个点只负责固定尺度的框回归。如果还出现重复，则选择尺寸最小

* 防止远离物体中心的点产生质量差的框，center-loss。$centerness^*=\sqrt{\frac{\min(l^*,r^*)}{\max(l^*,r^*)}\times \frac{\min(t^*,b^*)}{\max(t^*,b^*)}}$
  
  使<u>**左和右，上和下的长度尽可能相等**</u>。测试时centerness-weighted classification confidence，抑制偏远框👇
  ![](Figures/d39a52432c2c3225142d3500869baf40e3c73b58.png)
  网络结构👇
  ![](Figures/8b5702a9ed96bc002a55b079d5b531be343ca142.png)

- - - -

## CentripetalNet: Pursuing High-quality Keypoint Pairs for Object Detection

![image-20200428214951683](Figures/image-20200428214951683.png)

---

## SaccadeNet: A Fast and Accurate Object Detector

![image-20200428220100664](Figures/image-20200428220100664.png)

同时预测中心`Center Attentive Module`和角点`Attention Transitive Module`，得到粗框，使用`Aggregation Attentive Module`双线性插值重新采样feature map，得到精细框，<u>轻量级边框细化</u>。`Corner Attentive Module`辅助训练。

`Center-AM`<u>距离惩罚</u>训练，采用Gaussian heat map作为GT $e^{\frac{\left\|X-X_{k}\right\|^{2}}{2 \sigma^{2}}}$

相比CornerNet增加了中心特征，相比FCOS增加了边缘特征，相比CenterNet加速

## Mask RCNN

参考[https://zhuanlan.zhihu.com/p/37998710](https://zhuanlan.zhihu.com/p/37998710)

#### 网络结构

![](Figures/2020-02-17-23-33-00-image.png)

#### RoI Align

![](Figures/2020-02-17-23-32-25-image.png)

![](Figures/2020-02-17-23-33-41-image.png) 👆loss计算时`w*h*c`的mask输出，只计算<u>分类分支预测的类别</u>对应channel的sigmod输出作为损失「**语义mask预测与分类预测解耦**」

---

## HBONet: Harmonious Bottleneck on Two Orthogonal Dimensions

> light-weight 

包含两个部分 _spatial contraction-expansion_ 和 _channel expansion-contraction_ ，独立作用在特征图的 orthogonal dimension。前者通过减少特征图大小减少计算量，后者通过提升informative feature提升性能

> mobilenet通过分离成*point-wise*和*depth-wise*来分别不变尺寸变通道数和不变通道数变尺寸(up/down sampling)     so called *depthwise separable conv*  
> shufflenet通过group conv减少通道上的计算量，channel-shuffle来增加不同通道之间的连接  
> 👆previous work focus on **channel transformation**, introduce **spatial feature dim(size)**  

* 提升通道数可以提升信息，但是增加计算开销. 提出*Two reciprocal components work on orthogonal dimension*.<u>**通道数扩展时，尺寸减少**</u>
* 相比mobilenet增加**spatial contraction缩小-expansion放大到输入的大小**，类似Squeeze-Excitation Network的先缩后放的思路
  模块，对比mobilenet👇
  ![](Figures/7a0feef0d97e42bab4044301662546ba8c93851c.png)
  计算量👇
  ![](Figures/a43e53f7f1c22a59e7b1079ac38e14d39292c07b.png)
* 增加residual path，减少主干计算and **feature reuse**. Inverted residual with harmonious bottleneck👇
  ![](Figures/6c1529ac24e533703ca3c5dcdc70f721512e2ac1.png)
* For Object detection: use **MobileNet V2 SSD** utilize the **warm-up** strategy which linearly ramps up the learning rate from a close-to-zero one 1e-6 to the normal initial learning rate of 1e-3 during the first 5 epochs. 

---

### SSD网络时间

1. 网络运行时间：0.002-0.003s 在GPU运行
2. detect（NMS为主）运行时间：0.013-0.016s 只在 _CPU_ 上运行 <u>**瓶颈**</u>

尺度减少，aspect ratio减少
Shallow feature map only for small
Deep ONLY large
低秩简化
PointRend

<u>**特征融合
cascade**</u>

---

## Cascade RPN

<u>Single anchor per location + multi-stage refinement</u>

> 一次回归不到（距离太远），多次回归
>
> 回归多次后anchor点处的特征和移动anchor所在位置特征不匹配$\to$deformable conv
>
> 匹配的anchor位置不变(还是最初始点对应的anchor)，但是提取特征的位置改变👇👇

![图像](Figures/%E5%9B%BE%E5%83%8F.jpeg)

#### Motivation

predefined anchor在GT和anchor对齐时限制性能/偏差，(#toread RoIPool RoIAlign)

1. **single anchor** + incorporates **criteria** of anchor/anchor-free in defining **positive** boxes
2. **adaptive convolution** to maintain the alignment between anchor boxes and features

Iterative RPN每次把anchor集合**看作新的anchor**进行refine，导致每次迭代后anchor位置和形状发生变化，anchor和表示anchor特征不匹配「 **anchor中心点的特征(即表示anchor的特征)不发生变化，但是anchor的位置发生变化** ，mismatch」
👆使用deformable conv解决，but _no constraint to enforce_ 🙅‍♂️

#### Adaptive Convolution

卷积采样的时候增加offset field
`offset = center offset + shape offset`中心的偏移和形状偏移(由anchor形状和kernel决定)

![](Figures/d5cd3e96c3f74c043b11af85568fd780d34c03b6.png)

👆对比deformable conv：偏移量由anchor和kernel决定，非网络学习➡️anchor和feature对齐

#### Sample Discrimination Metrics

每个位置只有一个anchor，然后迭代refine

> Determining whether a training sample is pos/neg as the use of anchor/anchor-free is adversarial 两种方法决定正负样本的方法不同

👆即anchor-free的决定方式宽松/数量多，anchor-based标准严格/数量少
Stage 1: anchor-free➡️更多正样本「解决正负样本不匹配」
Stage 2: amchor-based➡️严格，数量减少，IoU高
`anchor-free`指FCOS，中心点在物体内为pos anchor
`anchor-based`指Faster RCNN，IoU threshold

#### Cascade RPN

前一个阶段的输出bridge到后一个阶段
由anchor计算出offset `o`，再和feature `x`输入regressor计算新的anchor ( $\sigma$就是anchor回归的目标 eg. $(tx-ax)/aw$ )

![](Figures/407d8090a6d3898e6971c85df18ba81b99684580.png)

---

## DetNet

> 为检测任务设计backbone  

现有的ImageNet backbone： 1. 网络stage需要增加，且未在imagenet训过 2. down-sample和stride损失空间信息，大目标边界模糊 3. 小目标「空间分辨率低」

---

## TridentNet

> Scale variation $\to$ Different <u>**receptive fields**</u>  

多分支网络，分支结构相同权重共享，每个分支不同的感受野对应检测不同尺度范围的物体
不同感受野使用`dilated_conv`实现👉参数相同
权重共享：减少参数量，inference时只选择一个主分支
![](Figures/ac7b0f86651341d53a16ca349d1b6deb5414d9c7.png)

<u>Image Pyramid</u> (Multi-scale training&testing): time-consuming
<u>Feature Pyramid</u>: use different params to predict different scale (not uniform) 

**trident block**👇

![](Figures/118a7989f6f926f41e2581e0c102f9c6d3c665e0.png)**Scale-aware Training Scheme**：每个branch只对长宽在一定范围的proposal进行训练「一张图片使用不同branch(不同dilate rate)训练不同尺度的proposal」
其他参数相同(make sense?) 

**预测**：计算每个分支的预测输出，filter out掉超过尺寸范围的box **TridentNet Fast**：预测只采用单分支$\to$中间分支预测，得益于三分支权重共享，效果接近

---

## SNIPER: Efficient Multi-Scale Training

> 解决多尺度问题, 不构建feature pyramid, <u>**多尺度训练策略**</u>, 尺寸适应网络

**Scale Invariant**: *RCNN*将proposal缩放到同一个尺度，检测网络只需要学习一种尺度的检测。而为了适应不同尺度，多尺度训练的*Faster RCNN*对整个图片进行放缩，proposal也放大缩小，检测网络学习适应多种尺度。 <u>通过网络capacity记忆不同scale的物体</u> ，浪费capacity

> *Process context regions around GT instances(chips) at appropriate scale*  
> 截取固定尺寸的chip(eg `3x3, 5x5, 7x7`)对应不同尺度，然后resize到相同大小(low-res)去训练  
> 小目标zoom-in，大目标zoom-out  

#### Pos chips

![](Figures/ff21eb5b057a444a8bb5207b3cc2b71dc5fdde7b.png)
👆chip从最小的cover某个GT box开始，直到最多的box被这个chip cover到
「chip尺寸不变，围绕cover这个GTbox转，直到最大化cover的box数量」

1. 每个box至少被一个chip cover
2. 一个物体可能被多个chip cover
3. 一个物体在不同尺度chip中可能valid or not
4. 截断的物体保留

#### Neg chips

![](Figures/58422bc9dea8dd52de0f8214533a4c54c7d97cc6.png)👆只有pos chips会导致网络只对GT附近小范围的图片训练 *iconic*，缺乏 <u>背景</u> 。增加**难样本**作为neg chips
Metrics:

1. 如果区域没有proposal，认为是easy background，忽略
2. 去掉被pos chip cover的proposal「proposal和GT接近，易于区分」
3. 贪心选择至少cover M个剩余proposal的作为neg chips

训练时可控制neg chip数量，类似OHEM
<u>分辨率和准确率关系可能不大，过多context可能不必要</u>
Ref: [目标检测-SNIPER-Efficient Multi-Scale Training-论文笔记 | arleyzhang](https://arleyzhang.github.io/articles/f0c1556d/)

---

## Stitcher: Feedback-driven Data Provider for Object Detection

> 小目标，粘贴构造训练样本

小目标数据集中分布不均匀(41.4%的小目标只出现在52.3%的图片中)，小目标在训练过程中贡献的loss低，学不好

把图片缩小，拼接在一起（和SNIPER切割相反）

![image-20200620175602128](Figures/image-20200620175602128.png)

**把大物体和中物体都变成小物体，增加小尺度的分布**

小目标：检测时放大❌，训练时缩小✅

loss作为反馈信号，**小目标产生loss不足($r^t_s<\tau$)则下个iter采用stitch，缺啥补啥**

![image-20200620175826519](Figures/image-20200620175826519.png)

![image-20200620175926012](Figures/image-20200620175926012.png)

---

## HRNet: Deep High-Resolution Representation Learning for Visual Recognition

> 处理过程中保持高分辨率「position-sensitive task」  
> maintain high-res representation through the whole process  
> 不同于skip connection：高分辨分支平行conv，通过fusion而不是add融合高低分支，多分辨率输出  
> 不同于特征金字塔：高低分辨率平行计算（low-res增加分辨率下conv计算，不是通过high-res一次卷积downsample得到，**逐步平行**计算增加）  

先前网络：encode high $\to$ low，recover low $\to$ high
提出网络：运算时**保持高分辨率**分支，**平行**的加入低分辨率分支；**multi-res fusion**

#### Parallel multi-res conv

![](Figures/24dc1e9896b61be4bef3511cd8a870ed0fd0e31c.png)👆每个stage <u>逐步加入一个低分辨率(eg 1/2)</u> 分支，且保持原有分辨率分支
类似 <u>group conv</u> ，通道分别 $\to$ 分辨率分别

#### Repeated multi-res fusion

每个stage(4个unit/block)交换不同分辨率的信息
![](Figures/e4187388dd2d925fbbd3c4f199e3d5e8c830eb90.png)👆high $\to$ low: stride conv; low $\to$ high: bilinear upsampling + 1x1 conv
an <u>extra</u> output for lower res output![](Figures/7ac095e7bf586fccf3c9b8de1caf0658163c37eb.png)👆融合类似FC

#### Multi-res representation head/不同任务不同输出模式

![](Figures/a2036193f4b7513cffb8bb02a77b3e3cbf9ab787.png)(a) 关键点检测 (b) segmentation (c) object detection

---

## Region Proposal by Guided Anchoring

> 更好的anchor，**改进产生anchor的过程**「非密铺」  
> anchor与feature: <u>**alignment**</u> + <u>**consistency**</u> 

两个分支分别对anchor的中心点和长宽进行预测，防止offset偏移过大，anchor和点的feature不对应
采用**deformable conv**使feature的范围和anchor的形状对应，每个位置anchor形状不同而capture不同的特征「加offset以适应anchor形状」
![](Figures/ec5348cb3efb80de6adb90ab09fac616f97681bd.png)

#### Guided Anchoring

$p(x,y,w,h|I)=p(x,y|I)p(w,h|x,y,I)$
**分两步产生anchor**「减小同时预测xywh时出现的偏移不对应」

1. location：预测objectness，之后采用mask_conv **减少区域计算**
   只对物体的中心(及附近)为pos训练，预测物体中心「边缘不容易回归框」
2. shape：预测每个位置上的best shape，位置不变只变长宽，不会misalign
   预测$w=k\times e^{dw}$，预测dw，而不是w，范围更大👇
   $w=\sigma \cdot s \cdot e^{dw}, \; h=\sigma \cdot s \cdot e^{dh}$

选择高于thresh的location中，概率最高的shape，产生anchor

#### Feature adaptation

**consistency**: 每点对应的anchor长宽不同，所以学习到特征对应区域的长宽也应该不同
$\mathbf{f}'_i=\mathcal{N}_T(\mathbf{f}_i,w_i,h_i)$
基于对应anchor的长宽，改变特征（xy不变，位置branch只预测objectness score）
👆使用deformable convolution实现

#### Anchor shape target

训练时anchor和gt box的匹配，训练目标。wh为变量，无法计算IoU

$\mathbf{vIoU}(a_{\mathbf{wh}},\mathbf{gt})=\max\limits_{w>0,h>0}{\mathbf{IoU}_{normal}(a_{\mathbf{wh}},\mathbf{gt})}$

方法：Sample常见的wh组合，计算和GT的IoU，得到vIoU👆，作为anchor和gt IoU的估计，之后采用常见anchor分配方法确定训练目标

#### High quality proposal

由于生成的anchor更好，pos样本数量更多。训练样本分布符合proposal分布
设置 <u>更高正负样本比例</u> ，同时 <u>更少样本</u> 数量，即 <u>更高IoU threshold</u>

---

## Soft NMS

> 解决密集 _相邻_ 物体的检测框重叠IoU大，可能在NMS过程中 <u>**误删**</u>  
> 密集物体检测有提升  

#### NMS

按照置信度排序，选择最大的box i保留。其余box中，与I的IoU>threshold的删除(置信度置为0)。再从剩下box选择最大保留，重复
![](Figures/98b46d0bb819b13145c34910d32fda6c602d7192.jpg)

#### Soft NMS

重叠IoU越大，置信度下降越多
置信度置为0变为更新IoU>threshold框的置信度
![](Figures/ec46758beec67fa960bc978c8fa18304cceee89d.jpg)
或
![](Figures/89ba0e23898e18e892d209b76c3c2b6602fe3e0e.jpg)
Ref: [NMS与soft NMS - 知乎](https://zhuanlan.zhihu.com/p/42018282)

---

## Adaptive NMS Refining Pedestrian Detection in a Crowd

> 密集场景下NMS误删
>
> 通过预测crowd程度动态选择threshold

密集位置提高IoU阈值保留临近框，稀疏位置降低IoU阈值删除冗余框

对于**每个物体**定义object density $$d_{i}:=\max _{b_{j} \in \mathcal{G}, i \neq j} \operatorname{iou}\left(b_{i}, b_{j}\right)$$ 

阈值计算过程 $$N_{\mathcal{M}}:=\max \left(N_{t}, d_{\mathcal{M}}\right)$$

NMS过程 $$s_{i}=\left\{\begin{array}{ll}s_{i}, & \operatorname{iou}\left(\mathcal{M}, b_{i}\right)<N_{\mathcal{M}} \\ s_{i} f\left(\operatorname{iou}\left(\mathcal{M}, b_{i}\right)\right), & \text { iou }\left(\mathcal{M}, b_{i}\right) \geq N_{\mathcal{M}}\end{array}\right.$$

测试时density通过网络`density subnet`预测，objectness map + bbox预测`concat`作为输入，`5x5`卷积(临近物体的信息)

![image-20200428211808639](Figures/image-20200428211808639.png)

![image-20200428211838035](Figures/image-20200428211838035.png)

在<u>cityperson</u>和<u>crowdhuman</u>密集数据集效果好

Ref: https://www.starlg.cn/2019/05/20/Adaptive-NMS/

---

## Fast NMS

![image-20200510104231573](Figures/image-20200510104231573.png)

按照conf顺序构建IoU矩阵，转为上三角。对$B_i$，如果$\exists x_{i,j}>\epsilon$，则去掉$B_i$，速度快

问题：没有去掉$B_i$时把之后的$x_{i\;\cdot}$失效，「横向传播」，可能多删除框。$B_i$被删除后，之后的框和$B_i$的IoU仍被考虑计算

## Cluster NMS

*Enhancing Geometric Factors in Model Learning and Inference for Object Detection and Instance Segmentation*

#### Cluster-NMS

改进`Fast NMS`，增加remove row $B_i$的操作

![image-20200510121557382](Figures/image-20200510121557382.png)

$b^{t-1}$表示$t-1$ iter的NMS indicator，t次iter时对$C^t$进行NMS

$A=diag(b)$表示根据上次NMS结果(indicator)，对已经被supressed的框去掉（i行置0，不考虑 $x_{i\;\cdot}$ ，和i框的IoU不计算）

$T=1$同`Fast NMS`，$T=N$同`NMS`

没有重合的box可以分成多个**cluster**并行处理

#### Score penalty reweigh + Cluster NMS

类似`Soft NMS`中不是直接去除box 「hard」，变成对score进行reweight「soft」，构成`Cluster-NMS_S`

$s_{j}=s_{j} \prod\limits_{i} e^{-\frac{(\boldsymbol{A} \times \boldsymbol{X})_{i j}^{2}}{\sigma}}$

j和其他box的IoU越大，score降低越多

不同于`Soft NMS`，只会被 <u>和更高conf的box有大IoU</u> 而受到惩罚，由于是上三角，只计算和更靠前box的IoU

#### Normalized central point distance + Cluster NMS

增加同`DIoU`类似的中心点距离$D$，构成`Cluster-NMS_S+D`

$s_{j}=s_{j} \prod\limits_{i} \min \{e^{-\frac{(\boldsymbol{A} \times \boldsymbol{X})_{i j}^{2}}{\sigma}}+D^{\beta}, 1\}$

#### Weighted NMS + Cluster NMS

`Weighted NMS`根据IoU和conf加权`merge`重叠框，输出**全新的框**「速度慢」

$\mathcal{B}=\frac{1}{\sum_{j} w_{j}} \sum_{\mathcal{B}_{j} \in \Lambda} w_{j} \mathcal{B}_{j}$

$\mathcal{B}$是加权融合后的全新的框，$\Lambda=\left\{\mathcal{B}_{j} | x_{i j} \geq \varepsilon, \forall i\right\}$为重叠框，权重$w_{j}=s_{j} I o U\left(\mathcal{B}, \mathcal{B}_{j}\right)$，**weighted combination**

conf从高到低，找到IoU>threshold的框，根据IoU进行加权求和，得到融合框；再对其他IoU<threshold的框计算 (https://github.com/sanch7/Weighted-NMS/blob/master/weighted_nms.py)

`Cluster-NMS_W`:

$\mathcal{C'}=\mathcal{s} \otimes \mathcal{C}$

$\mathcal{B}=\mathcal{C'}\times \mathcal{B}$

![image-20200510164152776](Figures/image-20200510164152776.png)

## Feature NMS: NMS by Learning Feature Embeddings

**密集重叠场景**下，只通过IoU不能判断是否是对同一个物体的预测。<u>**增加feature vec 距离判断是否是同一个物体的预测**</u>，距离小删除

![image-20200520113710926](Figures/image-20200520113710926.png)

当IoU无法判断时使用embedding判断是否是同一个物体

训练使用<u>Margin Loss</u>: $L=\frac{\sum_{i \in \mathcal{A}} \sum_{j \in \mathcal{A} \backslash\{i\}} L^{\prime}(i, j)}{|\mathcal{A}| \cdot(|\mathcal{A}|-1)}$

其中，pairwise loss: $L^{\prime}(i, j)=\left\{\begin{array}{ll}\max \left(0,\left\|\mathbf{f}_{i}, \mathbf{f}_{j}\right\|_{2}-(\beta-\alpha)\right), & \text { if } o b j(i)=o b j(j) \\ \max \left(0,(\beta+\alpha)-\left\|\mathbf{f}_{i}, \mathbf{f}_{j}\right\|_{2}\right), & \text { otherwise }\end{array}\right.$

---

## Matrix Nets: A New Deep Architecture for Object Detection (xNets)

> FPN处理不同大小的物体(特征金字塔)  
> 👇本文增加不同长宽比物体的处理 (大小金字塔+aspect ratio金字塔)  

![](Figures/f96e9e976eb7720d970f1810c8396bf598967513.png)
高度，宽度减半。左下右上剪枝(物体不常见)
性能提升不明显，相比CenterNet参数量减少
Ref: [参数少一半、速度快3倍：最新目标检测核心架构来了](https://mp.weixin.qq.com/s?__biz=MzA3MzI4MjgzMw==&mid=2650768067&idx=2&sn=7133cf90287c91b297d857a57bdd6481&chksm=871a46bdb06dcfab0f4092acc96db5b8dc88c34937e7ea1a5e813e7d53a165d2549db0640068&scene=21#wechat_redirect)

---

## IoU-Net

> Add localization confidence in NMS
>
> 可以看作一种精细化的前背景分类（soft）

#### NMS

1. 选择最大classification confidence的框$b_j$，加入集合$S$。
2. 其他所有不再集合中的框，如果和$b_j$的IoU大于threshold，则删去，简化重复框。
3. 重复知道没有框，$S$为结果。

使用分类置信度作为最开始选择框的依据，IoU用于计算分类置信度最大的框和其他框之间的重合度，删去框。

而IoU-Net使用预测的框和GT的重合IoU，即定位置信度，选择最大作为依据。在inference阶段发挥作用。

#### 预测IoU

![15689424793639](https://images-1256050009.cos.ap-beijing.myqcloud.com/15689424793639.jpg)
通过网络预测IoU：使用FPN作为骨干网络，提特征。使用PrRoI pooling替代RoI pooling

#### IoU Guided NMS

![15689426602716](https://images-1256050009.cos.ap-beijing.myqcloud.com/15689426602716.jpg)
Rank all detection bbox on localization confidence.

选择IoU最大的框，其他框重叠大于thres的框只使用他的最大conf score作为IoU最大框的conf「根据IoU选择，最大score修正conf」

#### Consider bounding box refinement as optimization

![15689722991024](https://images-1256050009.cos.ap-beijing.myqcloud.com/15689722991024.jpg)
通过预测IoU并产生梯度，更新bounding box，并通过判断分数的提升和差值来更新边界框
// ToRead

#### Precise RoI pooling

使用双线性插值来连续化特征图，任意连续坐标(x,y)处都是连续的
$f(x,y)=\Sigma_{i,j}IC(x,y,i,j)\times w_{i,j}$
$IC(x,y,i,j)=max(0,1-|x-i|)\times max(0,1-|y-j|)$是插值系数，xy连续，ij为坐标像素点。RoI的一个bin表示为左上角和右下角的坐标对。通过二重积分进行池化（加权求和）
$PrPool(\{(x_1, y_1),\;(x_2, y_2)\},\;F)=\frac{\int_{y_1}^{y_2}\int_{x_1}^{x_2}f(x,y)dxdy}{(x_2-x_1)\times (y_2-y_1)}$

![15689719523883](https://images-1256050009.cos.ap-beijing.myqcloud.com/15689719523883.jpg)

使用ResNet-FPN作为骨干网络，RoI pooling换成PrRoI pooling。同时IoU预测分支可以和R-CNN的分类和边界框回归分支并行工作.

---

## FreeAnchor: Learning to Match Anchors for Visual Object Detection

Related 对于anchor生成/分配/选择的改进：Guided Anchoring, IoU-Net, MetaAnchor [MetaAnchor - 简书](https://www.jianshu.com/p/a24d814613eb)

> 对于anchor和object的<u>**匹配方式**</u>的改进，Learn to match 

之前采用IoU最大的anchor进行分配：细长物体，最representative的特征不在物体中心，IoU最大$\neq$最representative

Assign策略需要满足：

1. **Recall**: 每个物体都能分配一个anchor

2. **Precision**: 区分background anchor

3. **Compatible NMS**: 高分类分数的anchor有好的localization

**matching过程看作MLE过程**，每个物体从bag of anchor中选likelihood probability最大的

#### Maximum Likelihood Estimation分析现有detector

训练损失函数，$C_{i,j}$表示j anchor和i 物体匹配「assign using IoU criterion」$\mathcal{L}(\theta)=\sum\limits_{a_j\in A_+}\sum\limits_{b_i\in B}C_{i,j}\mathcal{L}_{i,j}^{cls}(\theta)+\beta\sum\limits_{a_j\in A_+}\sum\limits_{b_i\in B}C_{i,j}\mathcal{L}_{i,j}^{loc}(\theta)+\sum\limits_{a_j\in A_-}\mathcal{L}_j^{bg}(\theta)$

把训练损失函数看作似然概率

$\begin{aligned}
\mathcal{P}(\theta) &=\mathbf{e^{-\mathcal{L}(\theta)}} \\
&=\prod_{a_{j} \in A_{+}}\left(\sum_{b_{i} \in B} C_{i j} e^{-\mathcal{L}_{i j}^{c l_{j}}(\theta)}\right) \prod_{a_{j} \in B_{+}}\left(\sum_{b_{i} \in B} C_{i j} e^{-\beta \mathcal{L}_{j_{j}}^{l o c}(\theta)}\right) \prod_{a_{j} \in A_{-} \atop a_{j} \in A_{-}} \mathcal{P}_{j}^{b g}(\theta) \\
&=\prod_{a_{j} \in A_{+}}\left(\sum_{b_{i} \in B} C_{i j} \mathcal{P}_{i j}^{c l s}(\theta)\right) \prod_{a_{j} \in A_{+}}\left(\sum_{b_{i} \in B} C_{i j} \mathcal{P}_{i j}^{l o c}(\theta)\right) \prod_{a_{j} \in A_{-}} \mathcal{P}_{j}^{b g}(\theta)
\end{aligned}$

<u>映射非常巧妙，使$[0,+\infty)$的损失映射到$(0,1]$，而且损失越小，$\mathcal{P}(\theta)$越大</u>

因此，最小化损失的目标转换为最大化似然概率

#### 改进detection似然函数

目标 recall，precision，compatible

**Recall**：每个obj构建bag of anchor，最大化其中anchor的cls和loc似然。每个obj一定存在一个anchor对应

$\mathcal{P}_{\text {recall}}(\theta)=\prod_{i} \max _{a_{j} \in A_{i}}\left(\mathcal{P}_{i j}^{c l s}(\theta) \mathcal{P}_{i j}^{l o c}(\theta)\right)$

**Precision**：即对anchor区分前背景，把背景anchor分出

$\mathcal{P}_{\text {precision}}(\theta)=\prod_{i}\left(1-P\left\{a_{j} \in A_{-}\right\}\left(1-\mathcal{P}_{j}^{b g}(\theta)\right)\right)$

其中$P\{a_{j} \in A_{-}\}=1-\max\limits_iP\{a_j\to b_i\}$ 表示anchor j不match任何物体。即anchor不match任何obj概率越高，anchor不属于背景的概率越低(1-)，才可以最大$\mathcal{P}_{\text {precision}}(\theta)$

**Compatible**: $P\{a_j\to b_i\}$表示j anchor匹配i obj概率，NMS按照cls分数选。所以改成loc分数「i j 的IoU」越大，匹配概率越高，P为关于IoU的<u>saturated linear</u>函数。步骤存在于$\mathcal{P}_{\text {precision}}(\theta)$中

![](Figures/2020-02-16-19-21-00-image.png)

横坐标为IoU

**似然函数**:    Jointly maximize

$\mathcal{P}'(\theta)=\mathcal{P}_{recall}(\theta)\times\mathcal{P}_{precision}(\theta)$

#### 改进似然函数推出Matching Mechanism

训练损失$\mathcal{L}'(\theta)=-\log\mathcal{P}'(\theta)$，使用FocalLoss

其中有max操作，但随机初始化的网络，所有anchor得分都低，max没有意义

改用**Mean-max**函数：$\operatorname{Mean}-\max (X)=\frac{\sum_{x_{j} \in X} \frac{x_{j}}{1-x_{j}}}{\sum_{x_{j} \in X} \frac{1}{1-x_{j}}}$

训练不充分时接近mean，使用bag中所有anchor训练

训练充分时接近max，选择最好的anchor训练

![](Figures/2020-02-16-20-55-42-image.png)

可视化，anchor assign confident (laptop)

![](Figures/2020-02-16-20-57-56-image.png)

相比baseline有提升3%. 使用ResNeXt-64x4d-101，**为multi-scale

![](Figures/2020-02-16-21-02-22-image.png)

Ref: [https://www.aminer.cn/research_report/5dedbde4af66005a4482453f?download=false](https://www.aminer.cn/research_report/5dedbde4af66005a4482453f?download=false)

---

## 密集小目标

Paper: <u>Benchmark for Generic Product Detection: A strong baseline for Dense Object Detection</u>

![](Figures/2020-02-21-21-03-09-image.png)

<u>Scale Match for Tiny Person Detection</u>    [method+dataset]

---

## Aligndet: Revisiting Feature Alignment for One-stage Object Detection

---

## FPN & Variants

所有FPN都使用backbone的多层特征图（经过`1x1`卷积）👇$C_{2..5}$

![](Figures/2020-02-22-16-21-13-image.png)

#### Top-down FPN

经典FPN，从最高层特征(semantic，low-res)经过upsample，和各同一级的特征图相加

给底层特征引入高层语义信息，益于小目标检测（低层特征图）

![](Figures/2020-02-22-16-25-08-image.png)

公式$F_{i}^{t}=\mathbf{W}_{i+1}^{\mathrm{t}} \otimes\left(U\left(F_{i+1}^{t}\right)+C_{i}\right)$

#### Bottom-up FPN

从最底层(high-res)向上逐次产生FPN层，向高层特征图传播低层的空间细节信息(spatial)

从低到高，融合「本层特征，高一层特征，上一层FPN」

![](Figures/2020-02-22-16-42-55-image.png)

公式$F_{i}^{b}=\mathbf{W}_{\mathbf{i}}^{\mathbf{b}} \otimes\left(D\left(F_{i-1}^{b}\right)+C_{i}+U\left(C_{i+1}\right)\right)$

$D\to$ downsample, $U\to$ upsample

#### Fusing-splitting FPN

上述两个FPN顺序逐次产生，先产生的层会对之后层影响(unfair)

首先分组**fuse**高层和低层的临近两组特征

$\alpha_s=C_4+U(C_5), \alpha_l=D(C_2)+C_3$

然后**merge**高层和低层的特征

$\beta_s=\mathbf{W_s^f}\otimes \mathrm{cat}(\alpha_s,D(\alpha_l))$

$\beta_l=\mathbf{W_l^f}\otimes \mathrm{cat}(U(\alpha_s),\alpha_l)$

再**split**产生不同层的特征

$F_2^f=U(\beta_l), F_3^f=\beta_l$

$F_4^f=\beta_s, F_5^f=D(\beta_s)$

![](Figures/4acfff9cac36f72acc7a0cc716f33e27be53fd47.png)

Ref: *MFPN: A NOVEL MIXTURE FEATURE PYRAMID NETWORK OF MULTIPLE
ARCHITECTURES FOR OBJECT DETECTION*

---

## Learning Data Augmentation Strategies for Object Detection

> **数据增强**，通过搜索来**combine** transformations

数据增强角度：1. Learn a **generator** to create data 2. Learn a set of **transformations** applied to existing data(本文)

常用transformer：image mirror，multi-scale training，crop-and-erase (occlude)，cut-and-paste

自动学习数据集对应的数据增强方式：AutoAugment

Policy search问题：K=5个sub-policies，每个包含N=2个操作。训练时随机选择sub-policy，顺序执行N。

操作两个参数「执行操作的概率，操作大小程度」👇

![image-20200228183031352](/Users/mk/Library/Application Support/typora-user-images/image-20200228183031352.png)

![image-20200228192437277](/Users/mk/Library/Application Support/typora-user-images/image-20200228192437277.png)

#### Transform

1. **Color operations**: 改变颜色通道，obj位置不变 `equalize, contrast brightness`
2. **Geometric ops**: 改变obj位置和大小 `rotate, ShearX, TranslationY`
3. **Bounding box ops.**: 只改变bbox内的图像 `BBox_Only_Equalize, BBox_Only_Rotate, BBox_Only_FlipLR`

#### Results

`Rotate` 旋转图片和bbox（<u>best</u>）

`Equalize` 直方图均衡化(Histogram equalization)，平衡不同灰度像素出现概率，增大对比度👇![A histogram which is zero apart from a central area containing strong peaks is transformed by stretching the peaked area to fill the entire x-axis.](https://upload.wikimedia.org/wikipedia/commons/thumb/c/ca/Histogrammeinebnung.png/300px-Histogrammeinebnung.png)

`BBox_Only_TranslateY` bbox内垂直变换，上下翻转

![image-20200228190923807](/Users/mk/Library/Application Support/typora-user-images/image-20200228190923807.png)

---

## YOLO

分格子(grids)，每个格子只预测规定数量bbox，只有当gt box的中心点落入grid内时，此grid负责预测这个gt。(*潜在问题：密集物体，多个中心点落入同一个grid，漏检*)

![img](Figures/1*4Y1PaY3ZgxKt5w84_0pNxw.jpeg)

网络输出`(x,y,w,h), box_confidence_score`，表示normalized长宽和<u>中心点</u>offset，以及置信度「表示objectness和位置准确性」

![img](Figures/1*e0VY6U1_WMF2KBoKQNZvkQ.png)

分grid$\to$每个grid产生k个预测$\to$保留高box_conf_score预测

其中$box\_conf\_score=P(object)\cdot IoU$，$conditional\_class\_prob=P(class_i|object)$

**class confidence score**: $box\_conf\_score\times cond\_cls\_prob=P(class_i)\cdot IoU$

表示分类和回归的准确率

![img](Figures/1*9ER4GVUtQGVA2Y0skC9OQQ.png)

**网络结构**👆：下采样+全连接回归预测

**Loss function**：包括分类损失，位置损失，objectness （$S\times S$grids, $B$ bbox each grids ）

1. **Classification loss**：类别，cond_cls_prob

   $\sum_{i=0}^{S^{2}} \mathbb{1}_{i}^{\mathrm{obj}} \sum_{c \in \text { classes }}\left(p_{i}(c)-\hat{p}_{i}(c)\right)^{2}$

2. **Localization loss**：只计算匹配了gt的grid

   $\begin{array}{c}
   \lambda_{\text {coord }} \sum_{i=0}^{S^{2}} \sum_{j=0}^{B} \mathbb{1}_{i j}^{\text {obj }}\left[\left(x_{i}-\hat{x}_{i}\right)^{2}+\left(y_{i}-\hat{y}_{i}\right)^{2}\right] \\
   \quad+\lambda_{\text {coord }} \sum_{i=0}^{S^{2}} \sum_{j=0}^{B} \mathbb{1}_{i j}^{\text {obj }}\left[(\sqrt{w_{i}}-\sqrt{\hat{w}_{i}})^{2}+(\sqrt{h_{i}}-\sqrt{\hat{h}_{i}})^{2}\right]
   \end{array}$

   where $\mathbb{1}^{\mathrm{obj}}_{ij}=1$表示grid i的第j个box负责预测物体，预测根号来使大小物体误差值对loss函数贡献不同「见平方根函数，x小增长快，x大增长慢。小值误差增长快，大值误差增长慢」

3. **Confidence loss**：objectness，区分前背景，使用$box\_conf\_score$即$C_i$计算

   $\sum_{i=0}^{S^{2}} \sum_{j=0}^{B} \mathbb{1}_{i j}^{\mathrm{obj}}\left(C_{i}-\hat{C}_{i}\right)^{2}$和$\lambda_{\mathrm{noobj}}\sum_{i=0}^{S^{2}} \sum_{j=0}^{B} \mathbb{1}_{i j}^{\mathrm{noobj}}\left(C_{i}-\hat{C}_{i}\right)^{2}$

采用**NMS**去掉重复框

**没有RPN可以让网络获得更多context，利于分类(fewer false pos.)**

### YOLOv2

**BN**，**高分辨率** (`224x224`上pretrain backbone，`448x448`上finetune)

**anchor** box，对grid内B个box增加先验知识，规定初始scale和shape，<u>focus on a specific shape</u>，训练更稳定   👇从左到右

**Anchor机制通过预定义scale和shape来引入先验知识**，bbox has strong patterns

![image-20200302192028409](Figures/image-20200302192028409.png)

去掉FC层，使用`1x1 conv`改变通道为`7x7x((4+1+20)x5)`，grid内5个anchor

![img](Figures/1*UsqjfoW3sLkmyXKQ0Hyo8A.png)

特征图奇数分辨率：大物体处于图片中心，奇数更好分which grid

去掉pooling

anchor**聚类**确定predefined scale&shape（👇数据点之间<u>距离表示IoU</u>大小，位置无意义）每类anchor配置看作一个cluster

![img](Figures/1*esSmI0UaMr-GrqkUGMg0hA.jpeg)

预测offset `[tx, ty, tw, th]`减少网络预测取值范围，增大可表示的数值范围👇

![img](Figures/1*gyOSRA_FDz4Pf5njoUb4KQ.jpeg)

增加**passthrough**，类似skip-connection。和浅层特征图`concat`预测小目标

**Multi-Scale Training**采用多个尺度训练适应尺度变化 `320x320, 352x352,..., 608x608` 10个batch的不同尺度图片训练

使用**DarkNet**作为backbone👇

![img](Figures/1*NBnDpz8fitkhcdnkgF2bvg.png)

### YOLO9000

使用hierarichical classification训练yolo，使用WordTree将分类和检测数据集混合训练，分9418类

### YOLOv3

**Multi-label classification**：输出一个label id而不是cat维向量，直接输出exclusive output，使用binary cross-entropy loss训练

每个目标只匹配一个anchor，没有匹配的anchor不计算cls和loc损失，只计算objectness

**FPN**：<u>在3个尺度的特征图上预测，每个grid预测3个anchor</u>，一共9种anchor配置

**Residual+DarkNet53**：卷积增加skip-connection

![img](Figures/1*biRYJyCSv-UTbTQTa4Afqg.png)

**FPN**

![img](Figures/70.jpeg)

Ref: https://medium.com/@jonathan_hui/real-time-object-detection-with-yolo-yolov2-28b1b93e2088

---

## IoU

评价预测和gt的距离，回归目标。具有**尺度不变形**

$\operatorname{IoU}=\frac{|A\cap B|}{|A\cup B|}$

训练$L_{IoU}=1-\operatorname{IoU}$

问题：

1. <u>没有重叠</u>时 IoU=0，没有梯度无法用IoU loss训练

2. 无法很好反映方向不一致时重叠

   ![image-20200303220421986](Figures/image-20200303220421986.png)

#### GIoU (Generalized)

$\operatorname{GIoU}=\operatorname{IoU}-\frac{|C\backslash(A\cap B)|}{|C|}$

其中$C$为包含A和B的最小凸多边形(enclosing convex)，多为矩形

A和B不重合时也可以优化，范围$[-1,1]$，不重合时为负数(provide moving direction)

关注**形状之间缝隙减小**，如👆2,3中缝隙导致GIoU更小

![img](Figures/v2-a6311e2e892658c42d52b939cb467975_1440w.jpg)

👆<font color="#00dd00">不重叠样本</font>，IoU=0，而GIoU为负值，有梯度

👆<font color="#666600">重叠样本</font>，不断优化过程中GIoU$\to$IoU

<u>使用IoU Loss $L_{IoU}$或$L_{GIoU}$训练</u>，相比Sommoth-L1和MSE能带来性能提升

#### DIoU (Distance)

> 好的bounding box regres. 标准需要考虑三个因素：**Overlap, Center Distance, Aspect Ratio**

直接优化两个框中心点的距离

$\operatorname{DIoU}=\operatorname{IoU}-\frac{\rho^2(b,b^{gt})}{c^2}$

其中$\rho$ (or 图中$d$)表示中心点的欧式距离（**L1可以吗？**），$c$表示包含两个框的最小闭包区域的对角线距离👇

![image-20200303230451277](Figures/image-20200303230451277.png)

相比GIoU：GIoU更强调对齐，只要对齐之后没有梯度，如👇，预测蓝色框和GT绿色对齐，没有缝隙，GIoU term=0「一框包括另一的情况」

![image-20200303230816475](Figures/image-20200303230816475.png)

而DIoU直接优化框中心的重合，距离近👇

![image-20200303230931086](Figures/image-20200303230931086.png)

![image-20200303232843528](Figures/image-20200303232843528.png)

👆IoU不重叠loss高，GIoU正垂直水平方向loss高（如👆👆👆图），DIoU较低

DIoU也可用于NMS中DIoU-NMS

#### CIoU (Complete)

$\operatorname{CIoU}=\operatorname{IoU}-\frac{\rho^2(b,b^{gt})}{c^2}-\alpha v$

$v=\frac{4}{\pi^2}(\arctan{\frac{w^{gt}}{h^{gt}}}-\arctan{\frac{w}{h}})^2$

$\alpha=\frac{v}{(1-\operatorname{IoU})+v}$

使用各种IoU loss训练👇

![image-20200303233112636](Figures/image-20200303233112636.png)

---

## HAMBox: Delving into Online High-quality Anchors Mining for Detecting Outer Faces

> 在线匹配，先回归出框，再anchor-target匹配计算loss

#### 实验/Motivation

![image-20200316221449869](Figures/image-20200316221449869.png)

👆anchor大，每个人脸匹配到的数量变多，但是匹配到人脸占所有人脸中占比下降，人脸recall下降

👆anchor小，每个人脸匹配到的anchor数量下降，但是大多数人脸都有匹配anchor，人脸recall上升

![image-20200316221821820](Figures/image-20200316221821820.png)

👆0.35为anchor和target match的threshold，所以89%的anchor都没有被match

![image-20200316221942813](Figures/image-20200316221942813.png)

==关键== 纵坐标代表face数量

match 1个anchor的face有2492张，anchor能产生的正确预测框（`IoU>0.5`，Correctly Predicted Bounding Box）对应的人脸有1968张 $\to$ <u>*大多数人脸都能通过anchor产生一个IoU高的预测框*</u>

预测框经过NMS之后能保留下来的人脸只有343张 $\to$ *<u>大多数人脸经过anchor产生的预测框都被NMS过滤掉，而导致这些face漏检</u>*

但是NMS只删除一个位置重复的框(IoU过大)，对于漏检的人脸，只要有框cover，就一定会保留，NMS后同一个位置至少保留一个score最大的框 $\to$ NMS后导致漏检的1625张face，产生了CPBB(`IoU>0.5`)，但是NMS被删掉 $\to$ IoU足够大，但是得分太低（低于`cls_threshold`)，NMS时过低score的忽略掉(不会考虑IoU) $\to$ *<u>是由于训练的时候此anchor没有match，分类分支训练目标为BG，分类网络降低了score</u>*「本质为IoU和score的mismatch」

👆**结论：低IoU而没有被match的anchor也能产生很好的预测框(CPBB)**，需要被match为物体，提高其分类score。这些anchor负责的face多为outer face(难样例)，上述也为outer face漏检的原因（低IoU框被unmatch，无法训练，分类网络不能分类为高分）

#### HAMBox (Online High-quality Anchor Mining)

选择大anchor，通过OHAM来进行弥补没有anchor match的face

**传统match策略**：一个face/target首先match所有<u>和它IoU大于threshold</u>的anchor。此后，对于没有anchor和它IoU高于阈值的face，选择<u>和它IoU最大</u>的anchor匹配进行补充（only one）

**OHAM**：1) match所有anchor IoU大于threshold的face，对于没有anchor匹配的face，不进行compensate. 2) 对所有框回归计算bbox. 3) 对所有没有匹配anchor的face，计算预测框和face的IoU，对其进行弥补，$\operatorname{IoU}>\operatorname{threshold'}$ 「没有匹配或匹配数量不足 (K anchor bag)」

**计算Loss学习时，使用回归后的bbox和target匹配，来弥补用原始anchor和target匹配的数量不足问题**

#### Regression-aware Focal Loss

$\begin{array}{l}
L_{c l s}\left(p_{i}\right)=\frac{1}{N_{c o m}} \sum_{i \in \psi} F_{i} L_{f l}\left(p_{i}, g_{i}^{*}\right) \\
+\frac{1}{N_{n o r m}} \sum_{i \in \Omega}\left(1_{\left(l_{i}^{*}=0\right)} 1_{\left(F_{i}<0.5\right)}+1_{\left(l_{i}^{*}=1\right)}\right) L_{f l}\left(p_{i}, l_{i}^{*}\right)
\end{array}$

其中$\psi$表示弥补的anchor，$N_{com}$为数量，p预测label，g=gt

$\Omega$为matched anchor和unmatched low-quality (IoU<0.5) anchor「即unmatched hq anchor不进行训练，应该hq仍未被match表示<u>简单样例上多余(>K)的anchor</u>」，$N_{norm}$为数量，$F_i$表示IoU，$l_i^*$表示第一次match的label

$\begin{aligned}
L_{l o c}\left(x_{i}\right) &=\frac{1}{N_{c o m}} \sum_{i \in \psi} L_{S m o o t h L 1}\left(x_{i}, x_{i}^{*}\right) \\
&+\frac{1}{N_{n o r m}} \sum_{i \in \Omega} L_{S m o o t h L 1}\left(x_{i}, x_{i}^{*}\right)
\end{aligned}$

![image-20200316225903344](Figures/image-20200316225903344.png)

---

## [RFB-Net] Receptive Field Block Net for Accurate and Fast Object Detection

> 不同感受野，对应不同扩张(dilation)
>
> **不是多尺度的特征图，而是不同感受野大小的特征图**

![image-20200321165433401](Figures/image-20200321165433401.png)

之前只变感受野(receptive field/kernel size)，或者只变扩张尺度(ASPP)

RFB提出感受野和扩张尺度应该同时变化「相互影响」

👇圈只表示感受野大小，<u>大的kernel对应大的dilate，使感受野更大</u>

![image-20200321165623460](Figures/image-20200321165623460.png)

实现上

![image-20200321165853355](Figures/image-20200321165853355.png)

使用两个`3x3`代替`5x5`。**注意padding，所有都为same size(k=3, p=1)，每个分支产生的特征图大小相同**

```python
self.branch0 = nn.Sequential(
                Conv(in_planes, 2*inter_planes, kernel_size=1, stride=stride),
                Conv(2*inter_planes, 2*inter_planes, kernel_size=3, stride=1, padding=visual, dilation=visual, relu=False)
                )
        self.branch1 = nn.Sequential(
                Conv(in_planes, inter_planes, kernel_size=1, stride=1),
                Conv(inter_planes, 2*inter_planes, kernel_size=(3,3), stride=stride, padding=(1,1)),
                Conv(2*inter_planes, 2*inter_planes, kernel_size=3, stride=1, padding=visual+1, dilation=visual+1, relu=False)
                )
        self.branch2 = nn.Sequential(
                Conv(in_planes, inter_planes, kernel_size=1, stride=1),
                Conv(inter_planes, (inter_planes//2)*3, kernel_size=3, stride=1, padding=1),
                Conv((inter_planes//2)*3, 2*inter_planes, kernel_size=3, stride=stride, padding=1),
                Conv(2*inter_planes, 2*inter_planes, kernel_size=3, stride=1, padding=2*visual+1, dilation=2*visual+1, relu=False)
                )
```

---

## [ASFF] Learning Spatial Fusion for Single Shot Object Detection

> 多尺度特征图融合

![image-20200321192646888](Figures/image-20200321192646888.png)

特征首先经过resize，再融合。*resize可使用deconv/conv, 插值/pooling*

$\mathbf{y}_{i j}^{l}=\alpha_{i j}^{l} \cdot \mathbf{x}_{i j}^{1 \rightarrow l}+\beta_{i j}^{l} \cdot \mathbf{x}_{i j}^{2 \rightarrow l}+\gamma_{i j}^{l} \cdot \mathbf{x}_{i j}^{3 \rightarrow l}$

Where $\alpha_{i j}^{l}=\frac{e^{\lambda_{\alpha_{i j}}^{l}}}{e^{\lambda_{\alpha_{i j}}^{l}}+e^{\lambda_{\beta_{i j}}^{l}}+e^{\lambda_{\gamma_{i j}}^{l}}}$, etc

and $\lambda_{\alpha}^l$, $\lambda_{\beta}^l$, $\lambda_{\gamma}^l$ computed (`1x1` conv) from $\mathbf{x}^{1\to l}$, $\mathbf{x}^{2\to l}$, $\mathbf{x}^{3\to l}$ **respectively**

<u>可以看作产生一个框feature pyramid多个特征图都用到，之前只用一个特征图产生一个框</u>

<u>**训练tricks**：mixup algorithm, cos lr, sync bn, bag of freebies</u>

---

## Accelerating Object Detection by Erasing Background Activation

> Objectness-aware object detection, 产生FG/BG的mask，只对mask区域计算

图片只有小部分有物体，背景区域不需要特征提取计算，**只对前景mask区域计算特征**，分类&回归(次要)出bbox

![image-20200324230634744](Figures/image-20200324230634744.png)

OMG网络为Fast-SCNN👇

![img](Figures/20190313161834869.png)

使用element-wise mul来zero-out背景的feature map

OMG中有`argmax`操作，为了end2end training，可以1) 使用`soft-argmax`代替`argmax`训练 2) 使用<u>surrogate gradient</u>，FP使用`argmax`，BP时使用`soft-argmax`代替获得近似梯度

$\operatorname{soft-argmax}(x)=\sum_{i} \frac{e^{\beta x_{i}}}{\sum_{j} e^{\beta x_{j}}} i$

**实验**： 对比MAC，使用不同mask监督

---

## Libra R-CNN: Towards Balanced Learning for Object Detection

> 训练方式，不平衡问题：hard example IoU分布不平衡，multi-level/res feature融合不平衡，不同loss样本产生的梯度不平衡
>
> 有梯度反推loss函数设计

**目标检测器训练目标**：

1. Selected region samples are representative
2. Extracted visual feature are fully utilized
3. Designed objective function is optimal

常见训练有三层次的imbalance

1. <u>Sample-level</u>: hard example需要多训练，但OHEM对噪声敏感
2. <u>Feature-level</u>: pyramid不同level/res的特征处理深度不同，高层处理多，浅/底层特征处理少
3. <u>Objective-level</u>: cls/reg两个任务损失函数协调

#### IoU-balanced Sampling

根据样本和GT的IoU，分成多个bin，每个bin均匀采样

第k bin中每个样本采样概率$p_k=\frac{N}{K}*\frac{1}{M_k},\;k\in[0,K)$

<u>**样本各IoU均匀分布**</u>

#### Balanced Feature Pyramid

使用同样深的网络来处理不同层的特征

resize不同层feature，**取平均**；使用Gaussian **non-local attention**增强融合的特征。在resize会原先的尺度增强multi-scale特征👇

![image-20200325222120052](Figures/image-20200325222120052.png)

#### Balanced L1 Loss

==**从梯度的角度考虑**== promoting the crucial gradient: 精确的样本(inlier)的梯度更重要，增强loss小的样本的梯度(<u>正确的梯度，数量少要增强</u>)，减弱loss大样本的梯度(<u>难训练，大梯度导致训练不稳定</u>)👇

![image-20200325232936319](Figures/image-20200325232936319.png)

$\frac{\partial L_{b}}{\partial x}=\left\{\begin{array}{ll}
\alpha \ln (b|x|+1) & \text { if }|x|<1 \\
\gamma & \text { otherwise }
\end{array}\right.$

👆增强小loss的梯度，大loss的梯度clip。<u>**大小loss样本产生的梯度平衡**</u>

$(x,y)\to Loss \to gradient$，**通过分析梯度，反推回loss设计**

积分可得👇

$L_{b}(x)=\left\{\begin{array}{ll}
\frac{\alpha}{b}(b|x|+1) \ln (b|x|+1)-\alpha|x| & \text { if }|x|<1 \\
\gamma|x|+C & \text { otherwise }
\end{array}\right.$

其中$x$为GT和pred的bbox坐标差距，$\gamma$为clip界 (大于$\gamma$，梯度恒定为1)，$\alpha$控制对小loss的梯度增强，$b$为平衡项，求出每个位置loss后mean或sum，即$L_{l o c}=\sum_{i \in\{x, y, w, h\}} L_{b}\left(t_{i}^{u}-v_{i}\right)$👇

![image-20200325234316019](Figures/image-20200325234316019.png)

#### Pipeline

![image-20200325234511396](Figures/image-20200325234511396.png)

---

## RepPoints: Point Set Representation for Object Detection

> Bbox特征不对齐问题，提供更好的object表示方法(不是中心点领域卷积)
>
> Deformable conv升级版，Representative Points
>
> 相比deformable，**直接使用变形后的结果作为预测的bbox位置（or anchor的偏移）**，而不是explicit回归xywh。中心点 + implicit-offsets + wh
>
> **采样点同时用来提取语义对齐的特征，又用来表示物体的几何形态**

![img](Figures/v2-a1bdfbed69d464815ddcd8f2ed097e96_1440w.jpg)

大部分为背景，需要选择更representative的点求特征

![image-20200326202246723](Figures/image-20200326202246723.png)

👆**训练**：分类网络采用deformable conv即可，回归网络先把reppoints表示转为bbox表示(pseudo box)，然后计算和GT的offset（point loss）

转换方式：1) <u>RepPoint set坐标最值</u> 2) subset坐标最值 3) 使用mean和deviation估计，$\mu$估计中心点，$\sigma$估计尺度(wh)

![image-20200326201955046](Figures/image-20200326201955046.png)

👆使用网络计算偏移量(offsets over the center points)，得到reppoint的点/物体特征表示$\mathcal{R}=\{(x_k,y_k)\}^n_{k=1}$，n个点特征表示sample points/object的特征。学习$\mathcal{R}_{r}=\left\{\left(x_{k}+\Delta x_{k}, y_{k}+\Delta y_{k}\right)\right\}_{k=1}^{n}$

👆维护两个RepPoint set，二次refine

**Learned via weak localization supervision from rectangular ground-truth boxes and implicit recognition feedback**

**使用基于中心点xy而不是xywh预测bbox，减少hypothesis space，一次只需要预测2D vec，更好训练**

#### RPDet

![image-20200326203026414](Figures/image-20200326203026414.png)

👆backbone FPN (多尺度即可解决基于点预测的重合物体问题，同FCOS)

👆两个分支：locate分支两次计算offset refine，class分支用offset变型卷积（dconv=deformable conv）

Ref: https://www.zhihu.com/question/322372759/answer/798327725

---

## Learning Rich Features at High-Speed for Single-Shot Object Detection (LSN)

> 分类任务预训练和检测任务gap，feature pyramid融合
>
> Light-weight Scratch Network产生准确底层特征输入FPN
>
> 底层特征高层特征双向传播

![image-20200424161122580](Figures/image-20200424161122580.png)

#### LSN

输入为downsample后的原始图片，低分辨率浅层网络 **train from scratch**

![image-20200424161326166](Figures/image-20200424161326166.png)

#### Bi-directional Network

**Bottom-up Scheme**👆👆(b)：$f_{k}=\phi_{k}\left(\left(s_{k} \otimes o_{k}\right) \oplus\left(w_{k-1} f_{k-1}\right)\right)$

$s_k$为LSN的特征输出，$o_k$为SSD (baseline)的输出，$f_{k-1}$为上一层特征，<u>cascade依次计算</u>

**Top-down Scheme**👆👆(c)：$$b_{k}=\gamma_{k}\left(\sum\left(W_{k} f_{k}, W_{m k}\left(\sum_{k+1}^{n} \mu_{k}\left(W_{i} f_{i}\right)\right)\right)\right)$$

$W_k$为`1x1`conv降通道，$W_{mk}$为`1x1` conv融合特征，<u>dense融合所有上层特征(low-res)</u>，$\mu_k$为`upsample`

先经过bottom-up再top-down，用top-down输出预测

#### Experiment

![image-20200424162957980](Figures/image-20200424162957980.png)

![image-20200424163032355](Figures/image-20200424163032355.png)

---

## Detection in Crowded Scenes: One Proposal, Multiple Predictions

> 一个anchor/候选框负责预测多个物体。anchor-GT 一对多
>
> 密集行人检测。密集，重叠/遮挡

![image-20200501145202227](Figures/image-20200501145202227.png)

之前：一个anchor负责预测一个物体；提出：<u>一个anchor预测一组</u>

对于一个anchor/prior/proposal $b_i$，预测的GT：$\mathrm{G}\left(b_{i}\right)=\left\{g_{j} \in \mathcal{G} | \operatorname{IoU}\left(b_{i}, g_{j}\right) \geq \theta\right\}$

预测为set：$\mathrm{P}\left(b_{i}\right)=\left\{\left(\mathbf{c}_{i}^{(1)}, \mathbf{l}_{i}^{(1)}\right),\left(\mathbf{c}_{i}^{(2)}, \mathbf{l}_{i}^{(2)}\right), \ldots,\left(\mathbf{c}_{i}^{(K)}, \mathbf{l}_{i}^{(K)}\right)\right\}$，$c_i^(j)$表示第$i$个anchor预测的第$j$个框的类别和置信度，$l$为位置

匹配时$K$个物体，但预测时仍可能部分预测结果为背景「<u>至多预测$K$个结果</u>」   *是否可以扩展为预测更多？*

训练看作最小化预测集和GT集之间的<u>推土机距离</u> $\operatorname{EMD}(P(b_i),G(b_i))$，和集合中位置无关，与分布有关

$\mathcal{L}\left(b_{i}\right)=\min _{\pi \in \Pi} \sum_{k=1}^{K}\left[\mathcal{L}_{c l s}\left(\mathbf{c}_{i}^{(k)}, g_{\pi_{k}}\right)+\mathcal{L}_{r e g}\left(\mathbf{l}_{i}^{(k)}, g_{\pi_{k}}\right)\right]$

预测的背景box计算$\mathcal{L}_{cls}$不计算$\mathcal{L}_{reg}$

#### 推土机距离 (Earth Mover's Distance, Wasserstein)

两个分布间距离：从一个分布变化到另一个分布所需要的最小做功

![img](Figures/v2-a157b48ccb585193b1074fa09f2e3f83_1440w.jpg)

![Screen Shot 2018-03-03 at 6.11.00 PM.png](Figures/screen-shot-2018-03-03-at-6-11-00-pm.png)

Ref: https://jeremykun.com/2018/03/05/earthmover-distance/, [https://zxth93.github.io/2017/09/27/KL散度JS散度Wasserstein距离](https://zxth93.github.io/2017/09/27/KL散度JS散度Wasserstein距离/index.html), https://zhuanlan.zhihu.com/p/74075915

#### Set NMS

一个anchor预测的多个物体是unique的，重复预测只可能出现在不同anchor预测集之间

NMS时增加：如果两个pred-box出自同一个anchor，则不进行抑制

#### 网络架构

![image-20200501151947284](Figures/image-20200501151947284.png)

`FPN`，增加`RoIAlign`

更多预测，可能出现更多False positive，可增加`Refinement Module`进行二次预测refine

![image-20200501152246868](Figures/image-20200501152246868.png)

Cityperson, CrowdHuman效果好

---

## AugFPN: Improving Multi-scale Feature Learning for Object Detection

> FPN改进，特征融合

![image-20200512164653675](Figures/image-20200512164653675.png)

#### Consistent Supervision

不同尺度的特征图有semantic gap，增加一个监督信号来限制学习到的特征的差异

增加多个<u>共享权重</u>的<u>预测头</u>(detect head)对不同尺度特征图($M_{1..5}$)上的proposal进行<u>预测</u>，加监督信号「**multi-head prediction**」

$\begin{aligned}L_{r c n n}= &\lambda\left(L_{c l s, M}\left(p_{M}, t^{*}\right)+\beta\left[t^{*}>0\right] L_{l o c, M}\left(d_{M}, b^{*}\right)\right)\\ &+L_{c l s, P}\left(p, t^{*}\right)+\beta\left[t^{*}>0\right] L_{l o c, P}\left(d, b^{*}\right)\end{aligned}$
其中$p_M,\;d_M$表示中间层的预测，$p,\;d$表示最终层的预测，$t^*,\;b^*$表示GT的label和box

#### Residual Feature Augmentation

最高层特征没有上层特征与其融合。采用不同尺度的$C_5$特征进行组合得到$M_6$，并融合到$M_5$中，来**增强最高层特征**

![image-20200512165827388](Figures/image-20200512165827388.png)

`Ratio-invariant Adaptive Pooling`为把$C_5\;@S$ pooling到不同尺度$(\alpha_1\times S, \alpha_2\times S,...,\alpha_n\times S)$

其中`Adaptive Spatial Fusion`为

![image-20200512165942891](Figures/image-20200512165942891.png)

#### Soft RoI Selection

*two RoIs with similar sizes may be assigned to different levels*

使用`ASF`对多层特征进行加权融合，作为RoI的特征

融合为了使anchor-feature的匹配不只是一对一，临近尺度的特征图也**参与预测**，一个样本**学习信号**也传到多个尺度特征图

---

## Learning to Separate: Detecting Heavily-Occluded Objects in Urban Scenes (SGE/Serial R-FCN)

> 密集检测，embeding+NMS (类似feature NMS)，cascade

密集检测中不同类物体的区分和同一类不同物体的区分

#### Semantics-Geometry Embedding & SG-NMS

增加将检测框映射到隐空间中	$e=\mathbf{s}^T\cdot \mathbf{g}$，其中$\mathbf{g}$即为检测框$(x,y,w,h)$，$\mathbf{s}$为语义嵌入向量。可以看作**将位置信息以语义信息作为权重进行线性变换得到embed**

box和GT<u>匹配时</u>，对每个proposal $b_i$，选择最大IoU的物体$b^*_j$，如果i和j的IoU大于阈值，则认为i proposal匹配到j物体。**Select max then thresholding**

<u>损失函数</u>增加 1. Group：proposal的embed和匹配的物体的embed距离尽可能小 2. Sep：proposal的embed和与其第二大IoU的物体的embed距离增大（**第一大的obj: 距离减小，第二大的obj: 距离增大**）

<u>NMS时</u>，IoU小于阈值$N_T$的保留(Greedy)，大于阈值的计算**embed的距离**(SG)，embed距离大于$\Phi$的保留，$\Phi\propto\operatorname{IoU}$，**IoU大的两个物体需要有更大的embed距离**

![image-20200608203857935](Figures/image-20200608203857935.png)

由于<u>FPN</u>作为backbone有多层，在FPN的每一层进行Greedy+SG NMS。在不同层之间只进行Greedy-NMS，且一个box只会被FPN其他层的box抑制

#### Serial R-FCN

![image-20200608205053055](Figures/image-20200608205053055.png)

分类分支和SG计算分支在回归分支之后cascade进行。**直接使用refined-box而不是RoI/proposal进行特征提取**，可以使用更高的IoU阈值来训练分类分支

分类分支辨别回归分支回归的refined-box属于类别/BG。随着回归分支能力增强，BG类别样本数量减少，需要**hard negative mining**。在refined-box上增加<u>随机噪声</u>输入分类分支，作为接近且低于IoU阈值的难负样本

![image-20200608205026817](Figures/image-20200608205026817.png)

所有分支都采用Position Sensitive RoI-Pooling👇，并增加self-attention👆

![img](Figures/v2-247cdb8e1305f64996fbd336813ce80e_1440w.jpg)

proposal/RoI区域内的每个位置有一个特征图，在对应特征图上RoI区域内pooling得到结果对应位置的响应值

Ref: https://zhuanlan.zhihu.com/p/30867916

---

## VoVNet

相比densenet，只进行一次特征融合操作

![image-20200620214131006](Figures/image-20200620214131006.png)

轻量级网络平DenseNet性能（不明显 $\approx 33@all$）

VoVNetV2 增加残差连接和SE-block

---

## DRConv: Dynamic Region-Aware Convolution

> 动态选择卷积核，不是receptive field。类似空域和通道上的attention

**空间的动态卷积核**，卷积核区域间不同，区域内共享

传统卷积核：通道间不同，区域间完全相同（共享卷积核）$W_c$

局部卷积：不同位置**pixel**卷积核不同$W_{u,v,c}$

$Y_{u, v, o}=\sum_{c=1}^{C} X_{u, v, c} * W_{u, v, c}^{(o)} \quad(u, v) \in S$

DRConv：不同区域卷积核不同，同一个区域内共享$W_{t,c}$

$Y_{u, v, g}=\sum_{c=1}^{C} X_{u, v, c} * W_{t, c}^{(o)} \quad(u, v) \in S_{t}$

首先学习划分区域mask，之后在每个区域内进行动态卷积

#### Learnable guided mask

学习分区，学习卷积核在特征图上的分布

使用普通卷积计算特征图（kernel空域上相同，通道维不同），**在特征图通道维选择最大的对应的卷积核**作为该位置上使用的卷积核

![image-20200620223935673](Figures/image-20200620223935673.png)

$M_{u, v}=\operatorname{argmax}\left(F_{u, v}^{0}, F_{u, v}^{1}, \cdots, F_{u, v}^{m-1}\right)$，m个channel

选择**通道维**最大的kernel作为区域的kernel (同样大小不同参数)

由于argmax没有梯度(mask $M_{u,v}$是one-hot向量)，所以反向传播时使用softmax取代$M_{u,v}$

$\hat{F}_{u, v}^{j}=\frac{e^{F_{u, v}^{j}}}{\sum_{n=0}^{m-1} e^{F_{u, v}^{n}}} \quad j \in[0, m-1]$

#### Dynamic Filter

**根据输入特征动态产生**每个区域的卷积核

类似通道+空域的attention机制（每个区域选择最大通道对应的卷积核）

性能提升1-2点 Mask-RCNN

---

# Object Detection Tricks

## Bag of Freebies for Training Object Detection Neural Networks

#### Visually Coherent Image Mixup Training

按照beta分布融合两张图片训练，位置信息不变（geometry preserved）求loss时按照融合占比加权

![image-20200701100926363](Figures/image-20200701100926363.png)

Beta distribution

![image-20200701101103962](Figures/image-20200701101103962.png)

效果：解决 **unprecedented** scenes (如屋中大象) 和 very **crowded** object group，但可能会使置信度降低

#### Label Smoothing

分类头上使用，增加CE-Loss中错误label的梯度，防止模型too-confident & over-fitting

$q_{i}=\left\{\begin{array}{ll}1-\varepsilon & \text { if } i=y \\ \varepsilon /(K-1) & \text { otherwise }\end{array}\right.$

#### Data Augmentation

* Random geometry transformation: crop, expansion, flip, resize
* Random color jittering: brightness, hue, saturation, contrast

二阶段有proposal的剪裁不需要geometry transformation

#### Training Schedule

采用cosine学习率，防止step scheduler剧烈变化不稳定

warm-up防止训练初期梯度爆炸

![image-20200701102240277](Figures/image-20200701102240277.png)

#### Sync BN

Batch-size 对性能影响大

`model = apex.parallel.convert_syncbn_model(model)`

#### Multi-scale

---

**Multi-scale training $\to$ Image level pyramid**

**Multi-level/stage feature $\to$ Feature pyramid**

相比image pyramid，特征金字塔只提取一次图像特征，不同stage输出（多尺度），速度更快

Multi-scale training + Feature pyramid $\to$ all in

## Scale-Equalizing Pyramid Convolution for Object Detection (SEPC)

>采用3D卷积进行多尺度特征融合，不同层融合权重不同

特征金字塔不同层之间存在semantic gap，之前采用feature fusion解决但没有提取intrinsic property

**Pyramid Conv** `PConv`: **在尺度维上 (不同层特征图)** 做卷积（like spatial conv），3D conv

选择三层，底层采用stride卷积，中间普通卷积，上层bilinear upsampling。控制不同层的不同stride来获得相同大小的输出，并相加。时间成本为1.5倍

![image-20200704214032431](Figures/image-20200704214032431.png)

BN修改为整个特征金字塔层共享统计量，效果类似sync_bn，同步不同位置上的统计量，统计范围更广

BN = standardization($\mu$,$\sigma$) + scale_shift($\gamma$,$\beta$)，统计卷积的bn为每张特征图，即channel维的统计，统计不同样本在同一个channel同一个位置的batch statistics $\mu$和$\sigma$（reduce at batch dimension）。每张特征图一对parameters $\gamma$和$\beta$

可以证明PConv能够提取Gaussian Pyramid(不同高斯模糊核对图片处理) 尺度不变的特征，即如果原图物体尺度变化，则可通过对PConv提取的特征shift得到改变后物体的特征 *<u>论文中有证明</u>*

**Scale-Equalizing Pyramid Conv** `SEPC`: PConv的升级版，通过deformable conv实现对不同尺度特征的对齐。

```python
def pconv_module_forward(x, conv2D_list):
	# x: input feature list [p3,p4,p5,p6,p7] # conv2D_list: conv2D module list,
	# [nn.Conv2D(stride=2),nn.Conv2D(),nn.Conv2D()]
	out_x = []
	for level in range(len(x)):
		tmp = conv2D_list[1](x[level])
		if level > 0:
			tmp += conv2D_list[0](x[level-1])
		if level < len(x) - 1:
			tmp += Upsample(conv2D_list[2](x[level+1])
		out_x.append(tmp) 
	return out_x
```

最底层普通卷积kernel size不变，其他层使用deformable conv

![image-20200704213956083](Figures/image-20200704213956083.png)

因为feature pyramid中由于backbone非线性操作，相对于gaussian pyramid特征不对齐，所以只通过dilation提取特征不全面，改用d-conv

*SEPC is an improved version of pconv, to relax the discrepancy of feature pyramid from a Gaussian pyramid by aligning the feature map of higher layers with the lowest layer*

底层特征采用普通卷积，卷积结果作为权重向上层的d-conv共享（卷积结果作为d-conv的一个输入求offset，类似CentripetalNet中）

SEPC模块用于取代RetinaNet的detection head的卷积模块

本质为一种pix-wise or fine-grained 的feature fusion，多尺度特征图通过卷积操作进行特征融合

![image-20200704214335943](Figures/image-20200704214335943.png)

性能提升明显

![image-20200704214411536](Figures/image-20200704214411536.png)

---

## Rethinking Classification and Localization for Object Detection (Double-Head RCNN)

> 检测头进行双路分支改进

二阶段检测器中，对proposal处理的传统检测头采用conv层，或者fast rcnn使用fc层处理

![image-20200706183720979](Figures/image-20200706183720979.png)

fc层作为head，由于全连接操作不同位置权重不共享，对于位置更加敏感（小位置变化大的输出结果变化），适合分类

conv层作为head，由于卷积操作不同位置权重共享，适合回归整个物体（coco2018结果表明可以使用conv层作为bbox的预测头）

![image-20200706185341027](Figures/image-20200706185341027.png)

分析conv作为head的分类回归结果👇

![image-20200706184401851](Figures/image-20200706184401851.png)

fc作为head的分类回归结果👆

1. 分类：fc作为head时，其高iou部分分类结果明显比conv作为head好。计算Pearson correlation coefficient👇fc-head的score-iou关系大于conv-head的score-iou关系

![image-20200706184732698](Figures/image-20200706184732698.png)

2. 定位：conv-head略好于fc-head

可视化关联关系：conv-head采用得到的特征图cos距离，7x7grid，每个点产生7x7大小的和其他任意点的关联矩阵；fc-head对fc层权重变换输出7x7特征图

![image-20200706185049024](Figures/image-20200706185049024.png)

conv-head计算的点和周围关联关系大

#### Double head RCNN

两个分支，conv-head用于回归，fc-head用于分类

![image-20200706185402627](Figures/image-20200706185402627.png)

改进：extend，训练时利用conv-head的分类损失和fc-head的回归损失进行监督(unfocused task supervision)

$\mathcal{L}^{f c}=\lambda^{f c} L_{c l s}^{f c}+\left(1-\lambda^{f c}\right) L_{r e g}^{f c}$, $\mathcal{L}^{c o n v}=\left(1-\lambda^{c o n v}\right) L_{c l s}^{c o n v}+\lambda^{c o n v} L_{r e g}^{c o n v}$

同时对分类分数进行二分支融合(classifiers are complimentary)

![image-20200706185811416](Figures/image-20200706185811416.png)

FPN+2.5~3.8 val AP

---

## D2Det: Towards High Quality Object Detection and Instance Segmentation

> 一阶段回归分支操作移植到二阶段
>
> deformable pooling + weighted pooling

![image-20200706234538094](Figures/image-20200706234538094.png)

#### Dense local regression

把RoI看作类似一阶段中的特征图。之前二阶段检测器对于一个RoI只预测一个框 (FC+预测)，改成RoI中每个点都预测一个框(dense prediction)。预测中间点到box上下左右的距离 (FCOS)

增加binary overlap prediction ($\hat{m}$)，对RoI和GT重叠部分为1，只有为1的点的预测结果有效。

<u>类似</u>一阶段中每点预测bbox，预测IoU/objectness

#### Discriminative RoI pooling

<u>deformable pooling + weighted pooling</u>

pooling的weighted权重通过输入特征操作得到（类似self-attention）👇W为计算的权重

$\tilde{F}=W(F) \odot F$

![image-20200707000247234](Figures/image-20200707000247234.png)性能提升较明显: multi-scale 50.1

---

## NMS by Representative Region: Towards Crowded Pedestrian Detection by Proposal Pairing (PBM)

>基于bi-box regre. 根据vis框进行NMS

行人检测中重叠，类内重叠Replusion Loss和AggLoss惩罚两个人中间的box，但是box的重叠仍然会导致在NMS过程中被误删

Adaptive NMS中GT-density和Pred-density的inconsistency

![image-20200707105643820](Figures/image-20200707105643820.png)

GT框不密集，但Pred-box是密集的。Adaptive NMS预测GT的密集程度，而NMS和Pred的密集程度有关。👆预测绿框不密集，所以红框不会被保留

#### NMS by representative region

通过计算visible部分的IoU而不是full部分的IoU进行NMS

重叠不同物体的检测框full-IoU大，vis-IoU小。重叠同一物体full-IoU和vis-IoU都大 $\to$ vis-IoU判别

![image-20200707132234249](Figures/image-20200707132234249.png)

#### Paired BBox Faster RCNN

Paired RPN + Paired Proposal Feature Extractor +  Pair RCNN

##### Paired RPN

GT标注为pair Q=(F,V)，全身框和可见框

**从一个anchor**回归出full和visible的proposal（为了inherent correspondence）

anchor和一对GT标注的匹配标准：

$\operatorname{IoU}(\mathrm{A}, \mathrm{F}) \geq \alpha_{1}$ and $\operatorname{IoF}(\mathrm{A}, \mathrm{V}) \geq \beta_{1}$

$\operatorname{IoU}(\mathrm{A}, \mathrm{F})=\frac{\operatorname{Area}(\mathrm{A} \cap \mathrm{F})}{\operatorname{Area}(\mathrm{A} \cup \mathrm{F})},\;\;\operatorname{IoF}(\mathrm{A}, \mathrm{V})=\frac{\operatorname{Area}(\mathrm{A} \cap \mathrm{V})}{\operatorname{Area}(\mathrm{V})}$

full和vis的回归训练策略同bi-box regression

##### Paired Proposal Feature Extractor

融合full/vis两个proposal的特征

![image-20200707133322847](Figures/image-20200707133322847.png)

<font color="#00dd00">绿色分支</font>+<font color="dd0000">红色分支</font>：简单的concat两个proposal的特征向量

<font color="00dd00">绿色分支</font>+黑色分支：visible region attention/mask，构建visible部分的0/1 mask，与full特征$F_f$点乘得$F_m$，再concat $F_m$和$F_v$

##### Pair RCNN

融合特征和proposal作为输入，两个分支分别预测full和vis的检测框

proposal和一对GT的匹配标准：

$\operatorname{IoU}\left(\mathrm{P}_{\mathrm{f}}, \mathrm{F}\right) \geq \alpha_{2}$ and $\operatorname{IoU}\left(\mathrm{P}_{\mathrm{v}}, \mathrm{V}\right) \geq \beta_{2}$

性能提升明显

![image-20200707134837180](Figures/image-20200707134837180.png)

---

## Hit-Detector: Hierarchical Trinity Architecture Search for Object Detection

>NAS整体搜索，基于FBNet

![image-20200708170606633](Figures/image-20200708170606633.png)

二阶段检测器：backbone + neck(feature pyramid & fusing) + RPN(fixed) + Head

NATS和DetNAS搜索backbone，NAS-FPN搜FPN，Auto-FPN搜fusing和Head

单独搜索效果较差，采用整体每个部件(backbone: $\alpha$, neck: $\beta$, head: $\gamma$)一起搜索，**end-to-end search**

$\alpha^{*}, \beta^{*}, \gamma^{*}=\underset{\alpha, \beta, \gamma}{\arg \min } \mathcal{L}_{v a l}^{d e t}\left(\alpha, \beta, \gamma, w^{*}(\alpha, \beta, \gamma)\right)=\underset{\alpha, \beta, \gamma}{\arg \min } \mathcal{L}_{v a l}^{d e t}\left(\alpha, \beta, \gamma, \underset{w}{\arg \min } \mathcal{L}_{t r a i n}^{d e t}(\alpha, \beta, \gamma, w)\right)$

每个component采用逐层搜索，构建每个操作用在每一层的得分矩阵$\alpha$，选择概率

对一个操作用在不同层的得分进行L2**正则化(column-space regularization)**，减少得分的数值大小：

$\min _{\alpha} f(\alpha)+\mu \min _{i}(\sqrt{\sum_{l=1}^{L} \alpha_{l, i}^{2}})$

选择$\alpha_{l,i}$最大max的一个操作，但为了可微采用softmax来选择(continuous relaxation)

搜索backbone时搜索空间的节点计算(differentiable)：$x_{l}=\sum_{o \in \mathcal{O}_{b}} \frac{\exp \left(\alpha_{l}^{o}\right)}{\sum_{o^{\prime} \in \mathcal{O}_{b}} \exp \left(\alpha_{l}^{o^{\prime}}\right)} o\left(x_{l-1}\right)$

搜索neck时搜lateral connection，搜索Head时搜fc预测前的block

优化时增加FLOPS约束：$\mathrm{C}(\alpha)=\sum_{l} \sum_{o \in \mathcal{O}_{b}} \alpha_{l}^{o} \mathrm{FLOPs}(o, l)$

首先固定$\{\alpha,\beta,\gamma\}$在一半的数据上训练求$\partial \mathcal{L}/\partial \mathcal{w}$更新$w$，再固定$w$在剩下的数据上训练求$\partial\mathcal{L}/\partial\alpha,\partial\mathcal{L}/\partial\beta,\partial\mathcal{L}/\partial\gamma$更新架构$\alpha,\beta,\gamma$

---

## SaccadeNet: A Fast and Accurate Object Detector

![image-20200708225553326](Figures/image-20200708225553326.png)

<u>Center Attentive Module</u>产生中心点和类别；<u>Attention Transitive Module</u>产生wh；<u>Aggregation Attentive Module</u>融合两分支的特征（双线性插值）和预测，并对预测框进行refine；<u>Corner Attentive Module</u>只有一个block产生角点预测，用于backbone监督信号，测试时去掉。

相比CenterNet改进：1. 通过Aggregation进行二步refine 2. 增加corner分支的监督信号有助于对边缘的检测（帮助预测wh的分支） 3. L1作为box训练损失

![image-20200708230331922](Figures/image-20200708230331922.png)

👆<u>test-dev</u>上性能，速度提升明显，快于yolov3

---

