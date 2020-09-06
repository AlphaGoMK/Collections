# Experiments

**Model**: `yolov3-416` 

**Train**: from https://pjreddie.com/darknet/yolo/

**Test**: val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.381
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.663
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.393
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.206
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.425
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.548
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.305
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.488
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.534
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.353
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.590
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.697
```

---

**FPS**: 29.7140 (batch=1), 33.1874 (batch=32)

---

==val结果==

**Model**: `yolov3-spp @416`

**Train**

**Test**: val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.404
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.672
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.425
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.210
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.440
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.592
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.312
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.505
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.550
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.360
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.603
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.721
```

**Speed**: 8.5/0.8/9.3 ms inference/NMS/total per 416x416 image at batch-size 32

---

**Model**: `yolov3-spp @608`

**Train**: 

**Test**: val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.440
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.713
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.476
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.276
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.470
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.590
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.332
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.539
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.588
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.448
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.622
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.724
```

**Speed**: 12.6/1.1/13.7 ms inference/NMS/total per 608x608 image at batch-size 32

---

**Model**: `yolov3-spp @608`

**Train**: 

**Test**: test-dev2017

```
overall performance
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.340
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.572   	# 60.6 on paper
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.354
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.144
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.356
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.487
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.286
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.457
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.489
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.265
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.528
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.666
```

---

**Model**: `yolov3 @416`

**Train:**

**Test:** test-dev2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.329
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.565
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.352
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.171
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.356
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.434
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.285
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.462
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.495
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.298
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.531
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.648
Done (t=597.14s)
```



---

**Model:** `yolov3-spp-ultralytics`

**Train:** multi-scale

**Test:** val2014 @640

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.453
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.646
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.492
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.261
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.499
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.595
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.360
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.594
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.660
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.487
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.711
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.808
```

---

**Model**: `yolov3-spp @416`

**Train**: 200 epoch

**Test**: test-dev2017

```
Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.255
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.470
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.254
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.113
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.284
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.349
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.238
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.411
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.467
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.276
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.524
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.600
```

---

**Model:** `yolov3-spp @416`

**Train:**

**Test:** val2017 IoU_thres=0.3

```
Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.389
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.666
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.402
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.199
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.427
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.571
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.310
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.476
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.503
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.318
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.553
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.665
```

---

==**Paper Results**==

Train/teste on <u>**COCO 2014**</u> (trainval+val5k, test-dev)

| Model         | mAP  | FPS @TitanX |
| ------------- | ---- | ----------- |
| `yolov3 @320` | 51.5 | 45          |
| `yolov3 @416` | 55.3 | 35          |
| `yolov3 @608` | 57.9 | 20          |
| `yolov3-tiny` | 33.1 | 220         |
| `yolov3-spp`  | 60.6 | 20          |

---

**只计算定位的mAP** (所有物体设为同一类，不计算分类错误)

```shell
Class         P         R   mAP@0.5        F1
  all     0.485     0.719     0.672			0.579
```

**分类定位都计算的mAP** (baseline)

```
Class         P         R   mAP@0.5			   F1
all        0.54     0.695     0.657     0.595
```



---

**两个物体距离过近，导致合成一个bbox**

val: `21167,42178,92939,156076,187249,175535,166426,243989,277051,493566`

**NMS错误？**

val: `104669,166426,270908,277051,440184,534270,496954,579091`

**Hard Example**

```shell
[(['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000425702.jpg'], tensor(9.41547, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000021839.jpg'], tensor(8.19916, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000500270.jpg'], tensor(8.09190, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000011197.jpg'], tensor(8.02103, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000521719.jpg'], tensor(7.95894, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000246883.jpg'], tensor(7.80300, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000494759.jpg'], tensor(7.66483, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000214224.jpg'], tensor(7.63128, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000561958.jpg'], tensor(7.54283, device='cuda:0')), (['/media/alpha/Data/MK/datasets/coco/COCO2017/val2017/000000132329.jpg'], tensor(7.46154, device='cuda:0'))]
```

---

`YoloV3-SPP`

**<u>Val2017 5000</u>**张图片，15000个feature map，36335个物体中

**使用GIoU**：有**5267**个feature map未匹配的anchor产生的pred box比匹配的pred box与target的IoU更高，有**1355**个物体没有被任何anchor匹配`len(matched)=0`。有**6929**个物体，unmatched anchor中产生的最好pred IoU比matched anchor中产生的最差pred IoU大`unmatch.max > match.min`匹配的不一定比不匹配的好。有**429**个物体，unmatched anchor能产生比所有match anchor更高的IoU`unmatch.max > match.max`「<u>最好的预测结果由unmatched anchor产生</u>」。有**61**个物体，<u>最高IoU的框是由邻居位置的anchor产生的</u>

**使用DIoU**：有**1355**没有任何anchor匹配，**4044**个feature map存在未匹配比匹配的IoU更高，有**3464**个物体`unmatch.max > match.min`，**266**个物体`unmatch.max > match.max`

**使用IoU**：有**1355**没有任何anchor匹配，**4027**个feature map存在未匹配比匹配的IoU更高，有**3347**个物体`unmatch.max > match.min`，**205**个物体`unmatch.max > match.max`

**<u>Train-2017</u>**中**849942**个物体，**31351**个物体没有匹配任何anchor，**4841**个物体`unmatch.max > match.max` (using IoU)

**Val-2017**中，*yolov3-spp*的anchor设置，anchor平均match的物体数量为:

`[11236, 15249, 16355, 15963, 15968, 13736, 13166, 9292, 3663]`

匹配的anchor生成的<u>预测框</u>平均IoU为:

`[0.5115, 0.5822, 0.5477, 0.5744, 0.5621, 0.6141, 0.5664, 0.6778, 0.7091]` (use_all_anchors, reject)

匹配时(build_target)预定义anchor与GT的IoU:

`[0.4438, 0.4450, 0.4263, 0.4362, 0.4297, 0.4358, 0.4374, 0.4622, 0.4513] ` (hpy.IoU_t = 0.225)

所有anchor生成的预测框平均IoU为:

`[0.2029, 0.3042, 0.3080, 0.3177, 0.3079, 0.2929, 0.2560, 0.2131, 0.1222] `(use_all_anchors, no reject)

在unmatched产生最好pred的情况下 (205个物体)，产生最好pred的unmatched anchor配置分别的数量(9种anchor，object level)：

`[2, 166, 30, 0, 1, 0, 2, 2, 2]`

产生最差pred的matched anchor数量:

`[190, 6, 3, 0, 2, 0, 2, 2, 0]`

**Train-2017**中，*yolov3-spp*的anchor设置，每种anchor平均match的物体数量(in 849942 obj)为:

`[263528, 356194, 378742, 371662, 371346, 318379, 305089, 217552, 86196]`

匹配的anchor生成的预测框的平均IoU为:

`[0.5112, 0.5804, 0.5482, 0.5724, 0.5620, 0.6158, 0.5687, 0.6756, 0.7154]`

在unmatched产生最好anchor的情况中 (4841个物体)，产生最好预测的未匹配anchor配置分别的数量:	(*按照每个anchor预测框和物体对应，出现一个物体最好预测为unmatch就对应的anchor种类就+1*)

`[139, 3829, 645, 54, 61, 21, 21, 9, 62]`，占所有不match的比例`[0.0002, 0.0078, 0.0014, 0.0001, 0.0001, 0.0000, 0.0000, 0.0000, 0.0001]`

产生最差pred的match anchor数量:

` [4395, 91, 206, 22, 33, 4, 73, 15, 2]`， 占所有match比例`[0.0167, 0.0003, 0.0005, 0.0001, 0.0001, 0.0000, 0.0002, 0.0001, 0.0000]`



---

#### COCO kmeans anchor设计

**yolov3-spp.cfg**

`(10,13), (16,30), (33,23), (30,61), (62,45), (59,119), (116,90), (156,198), (373,326)`

aspect ratio: `[0.492, 0.496, 0.533, 0.769, 0.788, 1.144, 1.289, 1.378, 1.435]`

**train2017@416** 

`(6.4403, 8.3782), (11.948, 17.055), (29.792, 20.809), (18.178, 38.191), (41.942, 45.698), (49.118, 101.06), (89.135, 64.018), (115.95, 144.11), (250.84, 239)`

aspect ratio: `[0.476, 0.486, 0.701, 0.769, 0.805, 0.918, 1.050, 1.392, 1.432]`

**val2017@416**

`(6.5551, 9.3417), (14.224,  16.74), (17.516, 37.016), (32.761, 24.814), (36.457, 65.152), (69.274, 47.337), (80.967,  107.1), (146.19, 165.71), (283.13, 244.43)`

aspect ratio: `[0.473, 0.560, 0.702, 0.756, 0.850, 0.882, 1.158, 1.320, 1.463]`

**latest**

`(6,9), (15,16), (17,35), (37,26), (36,67), (63,42), (57,100), (121,81), (112,169), (241,158), (195,310), (426,359)`

---

#### COCO物体遮挡重叠长宽比

**Train-2017**

有标注图片`117266`张，物体`860001`个，`5924155`个物体对之间

`1552007 (26.1%)`对框之间**最近距离小于10**，存在于`97635 (83.3%)`个图片中

`174292 (2.9%)`对物体bbox的**IoU>0.6**，存在于`51720 (44.1%)`个图片中

`43494 (0.73%)`对物体bbox的**中心距离小于10**，存在于`19937 (17%)`张图片中

`959 (0.82%)`张图片存在物体**聚集crowd** (7对及以上物体中心距离小于10)

`54951 (6.4%)`个物体**长宽比大于等于4**，存在于`30503 (26%)`张图片中

`504285 (58.6%)`个物体IoU最高的预测框不是objectness最高的预测框「**IoU-score mismatch**」

objectness最高的预测框IoU为IoU最高的预测框IoU的`74.97%`「选择objectness最高的预测框，则其IoU为最好的预测框的`74.97%`」

分类分数 (objectness*score) 最高的预测框IoU为最好预测框IoU的`74.69%`


**Val-2017**

有标注图片`4952`张，物体`36781`个，`255212`个物体对之间

`67616 (26.5%)`对框之间**最近距离小于10**，存在于`4125 (83.3%)`个图片中

`7648 (3.0%)`对物体bbox的**IoU>0.6**，存在于`2179 (44.0%)`个图片中

`1869 (0.73%)`对物体bbox的**中心距离小于10**，存在于`864 (17.4%)`张图片

`36 (0.73%)`张图片存在物体**聚集crowd** (7对及以上物体中心距离小于10)

`2272 (6.2%)`个物体**长宽比大于等于4**，存在于`30503 (25.5%)`张图片中

`21489 (58.4%)`个物体IoU最高的预测框不是objectness最高的预测框「**IoU-score mismatch**」

objectness最高的预测框IoU为IoU最高的预测框IoU的`75.06%`

分类分数最高的预测框IoU为最好预测框IoU的`74.56%`

最大的IoU，最大conf框的IoU，matched预测框的平均IoU，最大的conf，最大IoU框的conf，match的数量，最大iou的框面积，最大conf的框面积，$\frac{S_{\max conf}}{S_{\max iou}}$，最大IoU的偏移量，最大conf的偏移量的**均值**: `[0.7985, 0.6114, 0.5960, 0.5944, 0.2660， 3.5260, 8.6396, 9.9922, 1.6453, 1.9676, 2.3878]`，**方差**: `[0.1313, 0.2145, 0.1177, 0.3014, 0.3497， 1.0521, 10.9056, 11.4592, 2.0224, 1.0383, 1.0188]`

最高conf的框**平均偏大**，导致IoU不是最高

最高conf的框偏移量更大，最大IoU的框偏移量更小。从IoU视角，偏移量大的框，conf值不准确



---

## EfficientDet

**Model:** `eff-det-d0`

**Train:**

**Test:** val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.326
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.502
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.342
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.118
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.376
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.509
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.268
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.402
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.430
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.172
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.502
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.624
```

---

**Model:** `eff-det-d1`

**Train:**

**Test:** val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.382
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.568
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.407
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.181
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.437
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.555
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.304
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.465
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.496
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.266
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.562
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.673
```

---

**Model:** `eff-det-d7`

**Train:**

**Test:** val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.507
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.696
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.545
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.352
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.551
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.639
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.370
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.588
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.624
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.466
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.663
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.744
```

# YOLOv3

---

`COCO2014 trainvalno5k`，img=`416`，batch=`32`，加载`yolov3-spp` finetune，33个epoch，`last_spp_33_2014.pt`，mAP@0.5 = `0.523`

![results](Figures/results.png)

---

**Model:** `yolov3-spp`

**Train:** train2017, multi-scale, 300 epoches, 32 (more single-scale@416: 64)

**Test:** val2017

```
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.414
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.614
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.448
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.242
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.460
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.555
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.333
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.548
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.601
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.437
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.653
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.732
```

---

**Model:** `yolov3-spp` alpha=0

**Train:** pretrain2017 300epoch, coco1k, 600epoch, multi-scale, 16

**Test:** val2017

mAP@0.5$\approx$0.49-0.51

![results](Figures/results-2702289.png)

---

**Model:** `yolov3-spp baseline` 

**Train:** pretrain 300, coco1k, 600epoch, multi-scale, 8

**Test:** 

mAP@0.5$\approx$0.55-0.57

![results](Figures/results-2750106.png)

**Model:** `yolov3-spp pure-match`

**Train:** pretrain 300, coco1k, 470 epoch, m_s, 16

mAP@0.5$\approx$0.56-0.58

![results](Figures/results-2756847.png)

> 分成anchor-gt和pred-gt两部分的giou的损失
>
> 两部分分别计算损失

---

**Model:** `yolov3-spp split-match`  $\alpha=0.3$

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.59-0.61

![results](Figures/results-2844394.png)

**Model:** `yolov3-spp split-match` $\alpha=0.1$

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.59-0.61

![results](Figures/results-2872526.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.59-0.60

![results](Figures/results-2896735.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.0$

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.59-0.60

![results](Figures/results-2916705.png)

**Model:** `yolov3-spp split-match`  $\alpha=1.0$

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.48-0.50

![results](Figures/results-2978194.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$, iou_threshold_new 0.7

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.59-0.62

![results](Figures/results-3330624.png)

max: 0.6337 mean: 0.5875 std: 0.0148

为每个物体匹配top5/10最大IoU的anchor，只对lobj的训练有帮助（可能是减少正样本数量），对lbox训练没有帮助

![results](Figures/results-3685915.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$, iou_threshold_new 0.7, re-filter *new_iou*

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

max: 0.6122, mean: 0.5763, std: 0.0137

![results](Figures/results-3591536.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$, iou_threshold_new 0.7, re-filter *new_iou*, assign-rate 0.5x

```python
refilter: 
  new_iou = new_mat[:,1].view(-1,1)
assign-rate: 
  len(new_mat)/len(std_mat)
iou_threshold_new:
  n_idx = (obj_mat[idx,1]>=iou_thres).nonzero()
```

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

mAP@0.5$\approx$0.56-0.58

![results](Figures/results-3391920.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$ , assign-rate 0.5x

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6273 mean: 0.5897 std: 0.0118

![results](Figures/results-3823490.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$ , refilter

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6122 mean: 0.5763 std: 0.0137

![results](Figures/results-3848952.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$ , iou_threshold_new 0.7, assign-rate 0.5

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6368 mean: 0.5771 std: 0.0156

![results](Figures/results-3875566.png)

**Model:** `yolov3-spp split-match`  $\alpha=0.5$ , reduce_anchor

```python
max_iou, new_a = max_iou.max(dim=0) # [na,batch,ng1,ng0]
```

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6405 mean: 0.5907 std: 0.0147

![results](Figures/results-4658417.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.5$ , w/o std_mat in tobj

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.5805 mean: 0.5433 std: 0.0323

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$, w/o new_mat in tobj 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6218 mean: 0.5761 std: 0.0139

![results](Figures/results-4811951.png)



**Model:** `yolov3-spp fast-match`  $\alpha=0.5$ 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6134 mean: 0.5710 std: 0.0182

可能性能降低的原因：multi-object matched to one anchor

![results](Figures/results-4723784.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6312 mean: 0.6031 std: 0.0148

![results](Figures/results-4743626.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.3$ 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6244 mean: 0.5844 std: 0.0159

![results](Figures/results-4778074.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.7$ 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.5849 mean: 0.5554 std: 0.0248

![results](Figures/results-4794205.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$, remove_duplicate, remove_img 

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6363 mean: 0.5990 std: 0.0158

![results](Figures/results-5215375.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img, linear reweight 0.5

**Train:** pretrain 300, coco1k, 600 epoch, m_s, 16

Max: 0.6383 mean: 0.5923 std: 0.0165

![results](Figures/results-5471542.png)



## COCO 2017

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco2017, 323 epoch, m_s, 16

Max: 0.586

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco2017, 323 epoch, m_s, 16, lr 0.01-0.001

Max: 0.582

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco2017, 323 epoch, 416, 32, lr 1e-3~1e-4

Max: 0.577

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco2017, 323 epoch, 416, 32, lr 1e-2~1e-3

Max: 0.556

32 640

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img

**Train:** darknet, coco2017, 176 epoch, m_s, 16, lr 1e-2~1e-3

Max: 0.290

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img

**Train:** pretrain300.pth, coco2017, 24 epoch, m_s, 16, lr 1e-2~1e-3

Max: 0.567

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img

**Train:** pretrain300.pth, coco2017, 16 epoch, m_s, 16, smoothed_lr

Max: 0.564

**Model:** `yolov5s` 

**Train:** yolov5s.pt, coco2017, 25 epoch, 640, DDP 64=32x2

Max: 0.491

**Model:** `yolov5s` 

**Train:** yolov5s.pt, coco2017, 300 epoch, 640, DP 64x1

Max 0.52

**Model:** `yolov5s` 

**Train:** yolov5s.pt, coco2017, 30 epoch, 640, DP 32x2=64

Max: 0.488

**Model:** `yolov5s` 

**Train:** '', coco2017, 300 epoch, 640, DP 64x1, CIoU (maybe GIoU higher)

![results](Figures/results-7072259.png)

```shell
@672 conf=1e-3
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.350
 Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=100 ] = 0.548
 Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=100 ] = 0.375
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.197
 Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.403
 Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.444
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=  1 ] = 0.296
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets= 10 ] = 0.495
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.548
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=100 ] = 0.358
 Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=100 ] = 0.608
 Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=100 ] = 0.689
```



## COCO 5K

**Model:** `yolov3-spp pure-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco5k, 600 epoch, m_s, 16

Max: 0.5373 mean: 0.5219 std: 0.0073

![results](Figures/results-5260502.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ 

**Train:** pretrain 300, coco5k, 600 epoch, m_s, 16

Max: 0.5366 mean: 0.5238 std: 0.0064

0.525-0.533

![results](Figures/results-5120148.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.5$ 

**Train:** pretrain 300, coco5k, 600 epoch, m_s, 16

Max: 0.5279 mean: 0.5190 std: 0.0092

0.522-0.527

![results](Figures/results-5036053.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img

**Train:** pretrain 300, coco5k, 600 epoch, m_s, 16

Max: 0.5388 mean: 0.5199 std: 0.0075

![results](Figures/results-5327967.png)

**Model:** `yolov3-spp fast-match`  $\alpha=0.0$ , remove_dup, remove_img

**Train:** pretrain 300, coco5k, 600 epoch, m_s, 16, smooth lr0=1e-3

Max: 0.6075 mean: 0.5595 std: 0.0119

![results](Figures/results-5436811.png)



## MMDet

**Model:** `fcos_r50_caffe_fpn_gn-head_4x4_1x_coco`

```shell
Average Precision  (AP) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.359
Average Precision  (AP) @[ IoU=0.50      | area=   all | maxDets=1000 ] = 0.542
Average Precision  (AP) @[ IoU=0.75      | area=   all | maxDets=1000 ] = 0.383
Average Precision  (AP) @[ IoU=0.50:0.95 | area= small | maxDets=1000 ] = 0.204
Average Precision  (AP) @[ IoU=0.50:0.95 | area=medium | maxDets=1000 ] = 0.394
Average Precision  (AP) @[ IoU=0.50:0.95 | area= large | maxDets=1000 ] = 0.466
Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=100 ] = 0.538
Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=300 ] = 0.538
Average Recall     (AR) @[ IoU=0.50:0.95 | area=   all | maxDets=1000 ] = 0.538
Average Recall     (AR) @[ IoU=0.50:0.95 | area= small | maxDets=1000 ] = 0.336
Average Recall     (AR) @[ IoU=0.50:0.95 | area=medium | maxDets=1000 ] = 0.582
Average Recall     (AR) @[ IoU=0.50:0.95 | area= large | maxDets=1000 ] = 0.692
```

Time: 2d

