# COCO dataset

### COCO 2014

_2014 challenge在train和val同2015 challenge_
<u>**train 2014**</u> 82783
<u>**val 2014**</u> 40504
<u>**test 2014**</u> 40775，分为`test-dev, test-standard, test-challenge, test-reserve` ，在`iamge_info_test2014/2015.json`写明所有测试图片的信息，在`image_info_test-dev2015.json`中指明dev部分图片信息
Bounding box标注在`instances_train2014.json`中
Test-dev 2014的提交已被关闭
Coco标注从1开始，一共91类 `[1,91]`，但**其中11类数据集中没有**
_2014发布只有80类，后发布90类，1类为BG_ 

**目前可认为COCO有80类**

Ref: [https://tech.amikelive.com/node-718/what-object-categories-labels-are-in-coco-dataset/](https://tech.amikelive.com/node-718/what-object-categories-labels-are-in-coco-dataset/)

- - - -

### COCO 2017

**2017, 2018, 2019 challenge datasets are identical**
<u>**train 2017**</u> 118287
<u>**val 2017**</u> 5000
<u>**test 2017**</u> 40670，分为`test-dev, test-challenge`，前者为通用任务的测试集，包含的图片在`image_info_test-dev2017.json`标明；后者为特定workshop的数据集，在 `image_info_test2017.json`中除去test-dev的图片为test-challenge的所有图片集合
以上val数据集可用于提交的debugging

*trainval35k=train+val35k=train+val(40k)-minival(5k)*

- - - -

### COCO API

```
COCO       - COCO api class that loads COCO annotation file and prepare data structures.
decodeMask - Decode binary mask M encoded via run-length encoding.
encodeMask - Encode binary mask M using run-length encoding.
getAnnIds  - Get ann ids that satisfy given filter conditions.
getCatIds  - Get cat ids that satisfy given filter conditions.
getImgIds  - Get img ids that satisfy given filter conditions.
loadAnns   - Load anns with the specified ids.
loadCats   - Load cats with the specified ids.
loadImgs   - Load imgs with the specified ids.
annToMask  - Convert segmentation in an annotation to binary mask.
showAnns   - Display the specified annotations.
loadRes    - Load algorithm results and create API for accessing them.
download   - Download COCO images from mscoco.org server.
```

demo: https://github.com/cocodataset/cocoapi/blob/master/PythonAPI/pycocoDemo.ipynb
我的改进:[GitHub - AlphaGoMK/cocoapi: COCO API - Dataset @ http://cocodataset.org/](https://github.com/AlphaGoMK/cocoapi)
增加`showBBox(anns)`方法，输入anns参数为 _Result format_ 格式的dict，或者是标注格式

- - - -

### Submission

<u>**Result format**</u>     **JSON**

```
[{                                                                “image_id”: int,                                                 “category_id”: int,                                             
“bbox”: [x, y, width, height],                                     “score”: float,                             
}]
```

文件命名格式
`[type]_[testset]_[alg]_results.json`
[type]challenge type: “detections”, “person_keypoints”, or “stuff” 

[testset]test split: “val2017”, “test-dev2017”, or “test-challenge2017” 

[alg]your algorithm name

**压缩后提交**

提交地址：https://competitions.codalab.org/competitions/20794

参考：[COCO - Common Objects in Context](http://cocodataset.org/#guidelines)

### COCO Label Map

```python
{1: 0, 2: 1, 3: 2, 4: 3, 5: 4, 6: 5, 7: 6, 8: 7, 9: 8, 10: 9, 11: 10, 13: 11, 14: 12, 15: 13, 16: 14, 17: 15, 18: 16, 19: 17, 20: 18, 21: 19, 22: 20, 23: 21, 24: 22, 25: 23, 27: 24, 28: 25, 31: 26, 32: 27, 33: 28, 34: 29, 35: 30, 36: 31, 37: 32, 38: 33, 39: 34, 40: 35, 41: 36, 42: 37, 43: 38, 44: 39, 46: 40, 47: 41, 48: 42, 49: 43, 50: 44, 51: 45, 52: 46, 53: 47, 54: 48, 55: 49, 56: 50, 57: 51, 58: 52, 59: 53, 60: 54, 61: 55, 62: 56, 63: 57, 64: 58, 65: 59, 67: 60, 70: 61, 72: 62, 73: 63, 74: 64, 75: 65, 76: 66, 77: 67, 78: 68, 79: 69, 80: 70, 81: 71, 82: 72, 84: 73, 85: 74, 86: 75, 87: 76, 88: 77, 89: 78, 90: 79}
```

👆dict map从cocoapi标注到80维向量

##### COCO类别名称id对应表

| category       | anno_id | vec_idx |
| -------------- | ------- | ------- |
| person         | 1       | 0       |
| bicycle        | 2       | 1       |
| car            | 3       | 2       |
| motorcycle     | 4       | 3       |
| airplane       | 5       | 4       |
| bus            | 6       | 5       |
| train          | 7       | 6       |
| truck          | 8       | 7       |
| boat           | 9       | 8       |
| traffic light  | 10      | 9       |
| fire hydrant   | 11      | 10      |
| stop sign      | 13      | 11      |
| parking meter  | 14      | 12      |
| bench          | 15      | 13      |
| bird           | 16      | 14      |
| cat            | 17      | 15      |
| dog            | 18      | 16      |
| horse          | 19      | 17      |
| sheep          | 20      | 18      |
| cow            | 21      | 19      |
| elephant       | 22      | 20      |
| bear           | 23      | 21      |
| zebra          | 24      | 22      |
| giraffe        | 25      | 23      |
| backpack       | 27      | 24      |
| umbrella       | 28      | 25      |
| handbag        | 31      | 26      |
| tie            | 32      | 27      |
| suitcase       | 33      | 28      |
| frisbee        | 34      | 29      |
| skis           | 35      | 30      |
| snowboard      | 36      | 31      |
| sports ball    | 37      | 32      |
| kite           | 38      | 33      |
| baseball bat   | 39      | 34      |
| baseball glove | 40      | 35      |
| skateboard     | 41      | 36      |
| surfboard      | 42      | 37      |
| tennis racket  | 43      | 38      |
| bottle         | 44      | 39      |
| wine glass     | 46      | 40      |
| cup            | 47      | 41      |
| fork           | 48      | 42      |
| knife          | 49      | 43      |
| spoon          | 50      | 44      |
| bowl           | 51      | 45      |
| banana         | 52      | 46      |
| apple          | 53      | 47      |
| sandwich       | 54      | 48      |
| orange         | 55      | 49      |
| broccoli       | 56      | 50      |
| carrot         | 57      | 51      |
| hot dog        | 58      | 52      |
| pizza          | 59      | 53      |
| donut          | 60      | 54      |
| cake           | 61      | 55      |
| chair          | 62      | 56      |
| couch          | 63      | 57      |
| potted plant   | 64      | 58      |
| bed            | 65      | 59      |
| dining table   | 67      | 60      |
| toilet         | 70      | 61      |
| tv             | 72      | 62      |
| laptop         | 73      | 63      |
| mouse          | 74      | 64      |
| remote         | 75      | 65      |
| keyboard       | 76      | 66      |
| cell phone     | 77      | 67      |
| microwave      | 78      | 68      |
| oven           | 79      | 69      |
| toaster        | 80      | 70      |
| sink           | 81      | 71      |
| refrigerator   | 82      | 72      |
| book           | 84      | 73      |
| clock          | 85      | 74      |
| vase           | 86      | 75      |
| scissors       | 87      | 76      |
| teddy bear     | 88      | 77      |
| hair drier     | 89      | 78      |
| toothbrush     | 90      | 79      |

##### COCO 90类名称

person, bicycle, car, motorcycle, airplane, bus, train, truck, boat, traffic light, fire hydrant, ~~street sign~~, stop sign, parking meter, bench, bird, cat, dog, horse, sheep, cow, elephant, bear, zebra, giraffe, ~~hat~~, backpack, umbrella, ~~shoe~~, ~~eye glasses~~, handbag, tie, suitcase, frisbee, skis, snowboard, sports ball, kite, baseball bat, baseball glove, skateboard, surfboard, tennis racket, bottle, ~~plate~~, wine glass, cup, fork, knife, spoon, bowl, banana, apple, sandwich, orange, broccoli, carrot, hot dog, pizza, donut, cake, chair, couch, potted plant, bed, ~~mirror~~, dining table, ~~window~~, ~~desk~~, toilet, ~~door~~, tv, laptop, mouse, remote, keyboard, cell phone, microwave, oven, toaster, sink, refrigerator, ~~blender~~, book, clock, vase, scissors, teddy bear, hair drier, toothbrush, ~~hair brush~~
