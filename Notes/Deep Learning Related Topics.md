# Deep Learning Related Topics

## ResNeXt

> 传统为增加深度（层数）和宽度（特征维度），变成结合VGG的堆叠网络+Inception的 _split-transform-merge_ 策略。增加准确率和可扩展性同时不改变或减小复杂度  

提出<u>**cardinality**</u>，表示多分支的分支数量，more effective
![](Figures/EC005B55-327B-4F4C-A5FE-9232BA9D04E8.png)
👆左为ResNet，右为ResNeXt cardinality=32
<u>**平行堆叠**</u>代替线性加深，不显著增加参数数量级增加准确率；同时平行分支的拓扑结构相同减少了超参数（设计成本）
![](Figures/C1CCACF2-6F03-4B74-99C6-E8397306F05E.png)
👆split-transform-merge过程
![](Figures/E210EA79-5D84-4C33-B0BA-146AFABB08A2.png)
👆三种等价的结构，第三种简洁，速度更快

- - - -

## MobileNet

把传统卷积变成depth-wise卷积和1x1卷积
标准卷积（Dk卷积核大小，Df输出特征图尺寸，M输入通道，N输出通道）
$D_K\times D_K\times M\times N\times D_F\times D_F$
**深度可分离卷积**：depth-wise卷积和`1x1`卷积

$D_K\times D_K\times M\times D_F\times D_F + M\times N\times D_F\times D_F$

Depth卷积把输入特征图Dk x Dk x M成Df x Df x M层，然后`1x1`把M层变为N层输出
![](Figures/6B22C4FC-30D7-45C9-9CD8-DD3469070EDC.png)
👆<u>**depth-wise conv**</u>不同特征图通道使用不同卷积核，M层特征图卷积还是M层（不相加）所以`Dk x Dk x M x Df x Df`（一个卷积核计算`Dk x Dk`次，构成输出特征图的一个点，所以一张输出特征图一共计算`Dk x Dk x Df x Df`次，一共M层）
![](Figures/770C8B8D-2E90-4D9E-99D4-E1BE24CAE3A4.png)
👆depth-wise解释
![](Figures/C8B12662-17AF-4AE3-8753-17E1F0A5FAC0.png)
👆<u>**point-wise conv**</u>不同特征图使用同一个卷积核，但是1x1。把M通道卷积成N通道，所以`M x N x Df x Df` （一个卷积核计算M层相加，再计算N次构成N通道）
![](Figures/B1AE5F5A-4B07-4A4E-A1F3-932F477265B7.png)
👆point-wise解释

---

## Convolution

![](Figures/B712984B-A621-4D75-B9C1-7DB0D7D0226F.png)
![](Figures/4ECAAE30-D4AB-45FC-A130-F8DE831CC235.png)
参数量 `H x W x C1 x C2`

## Group Convolution

![](Figures/FB2404B4-04DF-4E98-923F-0E5DDB739C0A.png)
卷积核之间的关系是**稀疏**的。group conv减少卷积核之间的关联性， **regularization**，减少过拟合
Ref: [A Tutorial on Filter Groups (Grouped Convolution) - A Shallow Blog about Deep Learning](https://blog.yani.io/filter-group-tutorial/)

---

## MobileNet V2

增加<u>**inverted residual with linear bottleneck**</u>，首先升维，卷积，再降维。 <u>特征提取在高维空间进行</u> 。纺锤形，和resnet的hour-glass相反，所以inverted
在DW之前 <u>**增加PW卷积**</u>：上一层通道数少，则DW只能在低维空间提取特征，增加PW后，先升维，再提DW特征
![](Figures/20A1CAA2-880C-4C27-9475-C66CC955FDA5.png)
去掉了第二个PW的 <u>**激活函数**</u> ：只有在高维空间中，激活函数可以增加非线性；而在低维空间中，激活函数会破坏特征。因此采用线性
增加 **shortcut** 连接，输出与输入相加：同ResNet

- - - -

## ShuffleNet

> 组内point-wise卷积，增加shuffle操作通道之间信息沟通  

![](Figures/B747E511-B1B6-4CD8-9F8F-446708466A2B.png)
👆a：normal，b：分组卷积，c：channel shuffle

#### Channel shuffle

👇<u>**展开，转置，平铺**</u>
![](Figures/6C36658F-B3E1-4407-9517-D585F622C5BE.png)
![](Figures/3C97825C-0822-455C-AB65-9D0E27EB706C.png)
👆对比mobilenet，shufflenet和shufflenet降采样
👆g采用分组卷积，g小；去掉ReLU，减少信息损耗；降采样保证参数量不骤减，需要增加通道数量，采用concat而不是element-wise add
**性能评价**：MAC访存，GPU并行性
**设计准则**

* 当输入通道数和输出通道数相同时，MAC最小
* MAC与分组数量g成正比（谨慎使用分组卷积）
* 网络的分支数量降低并行能力（卷积核加载和同步），单分支速度快
  * ResNeXt准确率提升但是速度慢
* Element-wise操作是非常耗时

![](Figures/EA15DE00-DC00-4A95-B656-20AA985E0269.png)
👆shufflenet v2和downsample
增加**通道分割**，通道分为c1和c2输入到两个分支中，使用concat替代element-wise add
堆叠block的时候，可以将concat, channel-shuffle, channel-split合并为一个element-wise操作
思想—<u>**特征重用**</u>，上层的feature map直接传入之后的模块，直接映射（shufflenet v2左侧分支）

- - - -

## SqueezeNet

> <u>**分块设计**</u>思想，模型<u>**压缩**</u>

1. 使用`1x1`卷积代替`3x3`卷积  
2. 减少`3x3`卷积输入通道数  
3. 延迟下采样，前面layer获得更大特征图提升性能  

**Fire Module**

两层卷积操作：squeeze `1x1`, expand `1x1 + 3x3`
![](Figures/v2-5fde12f060519e493cb059484514f88a_hd.jpg)
👆👇 <u>squeeze是单分支，expand是二分支</u>  
![](Figures/1DCBEDA4-1CA7-4029-8E78-BF80ABEF9898.png)
部分3x3变成1x1，参数数量减少，但为获得性能需要加深网络深度，同时并行能力下降，也导致测试时间变长
![](Figures/v2-5f8ff8cb94babde05e69365336e77a62_hd.jpg)
👆网络结构

- - - -

## Squeeze-and-Excitation Networks
[arXiv](https://www.arxiv.org/pdf/1709.01507.pdf)  
卷积核：空间维度信息，特征维度信息聚集  
空间spatial：inception(multiscale)，inside-outside(context)  
SENet->特征维度,feature channel  
Motivation:
1. Explicitly model channel-interdependcies
2. Feature recalibration: enhance useful, suppress less useful

特征通道之间的关系：特征重标定（通过学习的方式来自动获取到每个特征通道的重要程度，然后依照这个重要程度去提升有用的特征并抑制对当前任务用处不大的特征）  
Squeeze: global pooling, 顺着空间维度压缩，增加全局空间信息，每一个二维特征图变为一个实数。表示特征通道上全局分布，加上S模块使得靠近输入的层也可以获得全局感受野  
Excitation: like gate in RNN. 每个通道生成权重，建模相关性，capture channel-wise dependencies  
W的要求 * learn non-linear interaction * learn a non-mutually-exclusive relationship since we would like to ensure that multiple channels are allowed to be emphasised opposed to one-hot activation  
Reweight: multiply with feature map  

嵌入Inception：  
嵌入ResNet： addition之前进行scale操作，防梯度弥散

---

## Hard Negative Mining in SSD & Focal Loss

1. Hard Negative Mining in SSD 作为中间结果处理的步骤。只有GT框/和GT框IoU大于阈值的才是正样本（即正确检测框，数量少），其他都是负样本（即错误的检测框，数量大）
   
   > <u>**为了正负样本数量平衡**</u>，防止少量关键的（提升性能）的负样本被大量正样本掩盖而无法被学习/优化到。   
   > 解决错误样例太多，<u>**正确样例太少**</u>，掩盖正确样例的问题。  
   
    **Hard Negative Mining in SSD**: 直接通过根据置信度损失，<u>**排序筛选**</u> 来选择分类损失最大的负样本（即不是物体但是有最高的分类置信度 -> 困难分类样本_迷惑性，丢弃不是物体但分类置信度相对较低 -> 简单_错误不严重/不明显），只保留分类置信度损失较大的，人为保证样本数量平衡。

2. Focal Loss 用于损失函数中
   
   > <u>**为了能学到困难样例**</u>，学到更多，不被简单掩盖。  
   > 解决错误样例中，<u>**简单的错误样例太多**</u>，困难错误样例太少，且求和后掩盖困难的错误样例，而导致检测器学不到困难的错误样例（真正需要学/优化的）。  
   
    **Focal Loss**: 通过给不同置信度的样本<u>**增加权重**</u>的方法。接近0/1为简单样本，接近0.5为难样本。所以正例x (1-p)，负例x p，使用 _不确定程度_ 作为权重。难易的错误都会学，但困难的错误对loss影响更大。
    $L(p,y)=-(y\cdots (1-p)\cdots \log(p)+(1-y)\cdots p\cdots\log(1-p))$

---

## One-stage & Two-stage detector

#### RCNN
![](Figures/6F235DE5-4774-4527-9FC9-F8EAF8252AEE.png)


## ICCV 2019 workshop

#### LPIRC

https://rebootingcomputing.ieee.org/lpirc/2019
Winner talk:  [http://ieeetv.ieee.org/conference-highlights/award-winning-methods-for-lpirc-tao-sheng-lpirc-2018?rf=series|3](http://ieeetv.ieee.org/conference-highlights/award-winning-methods-for-lpirc-tao-sheng-lpirc-2018?rf=series%7C3) 
 [http://ieeetv.ieee.org/conference-highlights/deeper-neural-networks-kurt-keutzer-lpirc-2018?rf=series|3](http://ieeetv.ieee.org/conference-highlights/deeper-neural-networks-kurt-keutzer-lpirc-2018?rf=series%7C3) 
_Real Time Object Detection On Low Power Embedded Platforms_
_1810.01732.pdf_

#### Compact and Efficient Feature Representation and Learning

http://www.ee.oulu.fi/~lili/CEFRLatICCV2019.html
DCNN network quantization and compression, energy efficient network architectures, binary hashing techniques and data efficient techniques like meta learning

---

## Triplet Loss

![](Figures/20150707120209693.png)
三元组: [anchor, positive, negative] 拉近pos，推远neg

$\mathcal{L}_{\mathrm{tri}}(\theta)=\sum_{a, p, n \atop y_{a}=y_{p} \neq y_{n}}\left[m+D_{a, p}-D_{a, n}\right]_{+}$

> 选出B个triplets，只用了B个训练，实际上可以有`6B^2-4B`种triplets的组合（_B个anchor，pos固定一对一，除此二其他所有都可以为neg，3B-2种；anchor和pos交换乘2_） `2*B*(3B-2)`种  

难训练，需要**triplet mining**。分出hard，semi-hard，easy三种样本
![](Figures/02_triplets.png)

1. <u>**Batch-Hard**</u>
   <u>选择P个类别（人），每个类别K个样本（照片），PK个样本作为anchor</u> 。每个anchor只选择**距离最远的pos和距离最近的neg**（最hard）
   
   $\mathcal{L}_{\mathrm{BH}}(\theta ; X)=\overbrace{\sum_{i=1}^{P} \sum_{a=1}^{K}}^{\text {all anchors}} \left[m +  \overbrace{\max_{p=1 \ldots K} D\left( f_{\theta}\left(x_{a}^{i}\right), f_{\theta}(x_p^i)\right)}^{\text {hardest positive}} - \underbrace{\min\limits_{j=1 \ldots P,\; n=1\ldots K \atop j \neq i} D\left(f_{\theta}\left(x_{a}^{i}\right), f_{\theta}\left(x_{n}^{j}\right)\right)}_{\text {hardest negative}}\right]_{+} $
   一共$P_K$个triplets

2. <u>**Batch-All**</u>
   选择P个类别（人），每个类别K个样本（照片），PK个样本作为anchor，loss计算所有的pos和所有的neg（和baseline选法相同）
   
   $\mathcal{L}_{\mathrm{BA}}(\theta ; X)= \overbrace{\sum_{i=1}^{P} \sum_{a=1}^{K}}^{\text {all anchors}} \overbrace{\sum_{p=1 \atop p \neq a}^{K}}^{\text{all pos.}} \overbrace{\sum_{j=1 \atop j \neq i}^{P} \sum_{n=1}^{K}}^{\text {all neg.}}\left[m+d_{j, a, n}^{i, a, p}\right]_{+}$
   
   $d_{j, a, n}^{i, a, p}=D\left(f_{\theta}\left(x_{a}^{i}\right), f_{\theta}\left(x_{p}^{i}\right)\right)-D\left(f_{\theta}\left(x_{a}^{i}\right), f_{\theta}\left(x_{n}^{j}\right)\right)$
   $P_K$个anchor，每个有$K-1$的pos，$P_K-K$个neg（其他所有类别的样本）。一共$P_K(K-1)(P_K-K)$个triplets

---

## Long Short Term Memory (LSTM)

> Handling long-term dependencies

LSTM blocks👇

![image-20191018172300763](Figures/image-20191018172300763.png)

#### Core idea

![image-20191018172422527](Figures/image-20191018172422527.png)

👆**Cell state** convey information straight down along the entire chain

![img](https://colah.github.io/posts/2015-08-Understanding-LSTMs/img/LSTM3-gate.png)

👆**Gate** controls whether add/remove information to the cell state

---

![image-20191018174346388](Figures/image-20191018174346388.png)

👆**Forget Gate**: how many last state information($c_{t-1}$) keep/forget.

![image-20191018174812836](Figures/image-20191018174812836.png)

👆**Input Gate**: what new information we’re going to store in the cell state.

Two parts: **sigmoid** layer decide which part of values we will update, **tanh** layer create a vector of new candidate values $\tilde{C}_t$

![image-20191018175359262](Figures/image-20191018175359262.png)

👆Apply to cell state: forget first, then partially add new candidate

![image-20191018175611169](Figures/image-20191018175611169.png)

👆**Output Gate**: decide what we’re going to output

Two parts: **sigmoid** layer decide which parts of the cell state going to output, **tanh** layer filters cell state. **Multiply** them together to get final output.

---

#### Variants

**1. Peephole Connection**

gate layer look at the cell state

![image-20191018192328653](Figures/image-20191018192328653.png)

**2. Input&Forget Together**

make what to forget and what to add together. Only forget when going to input something, only input when we forget.

![image-20191018192633284](Figures/image-20191018192633284.png)

**3. Gated Recurrent Unit**

Combines the forget and input gated into "update gate". Merge the cell state and the hidden state.

![image-20191018192913785](Figures/image-20191018192913785.png)

[Reference](https://colah.github.io/posts/2015-08-Understanding-LSTMs/)

---

## NASNet

> 先在小数据集中训练网络单元，再在大数据集中堆叠单元  

学习网络中堆叠的网络单元1. Normal cell尺寸不变 2. Reduction cell减尺寸
控制器：一直在执行两个特征图的<u>**融合**</u>
![](Figures/v2-88f671125c2996924eb8a2c5b48c965d_r.jpg)
选择第一个feature map和第二个feature map(灰色) `2` ，计算输入的feature map A B(黄色) `2` ，选择操作融合两个feature map(绿色) `1` 
RNN预测，输出`2 x 5 x B`其中 _normal cell_ + _reduction cell_ ；每个都有B个块堆叠；每个block有五个输出👆
NASNet迁移学习优化策略为Proximal Policy Optimization(PPO) 👈 
提出**scheduled drop path**，随机丢弃部分分支，增加网络冗余overfitting，类似「Inception」
丢弃概率随时间线型增加，训练次数多容易过拟合

---

## DetNAS

**weight sharing** inherit its weights from supernet instead of training from scratch
**joint optimization** weight and architecture
**No proxy task or dataset** 不需要提前训练小网络/小模块，也不需要从小数据集到大数据集训练
**train from scratch** 更多迭代，不适用于小数据集
首先训练(pretrain+finetune)一个supernet，然后再supernet空间中找；直接在det任务`Vdet`上搜索 <u>proxyless</u> 👇
![](Figures/DEEE8DD1-BD56-46A9-BA8A-6D16942C8049.png)
优点：

1. Decoupling: 没有weight和architecture之间的bias interaction

2. <u>supernet训好后，直接用val在supernet上搜索</u> 特定应用场景的结构，而不是finetune

#### 训练supernet👇

![](Figures/78DB7B34-1276-4AE0-AC78-0C38A7308692.png)

1. Single path sampling: 使训练和测试的配置一致
   ![](Figures/74B60042-F0B7-48C0-BC3E-47E80BE0E4B0.png)

2. 同步BN: <u>BN can not be frozen</u>, 不同path BN的参数不同（GroupNorm速度慢）

#### 搜索子网结构

遍历每个path，需要重新在trainset上搜集计算BN的mean和var
不用trainset训练子网，而直接在valset上eval

#### Target task dataset上finetune子网结构

---

## Self-supervised Sample Mining

> <u>**semi-supervised**</u> <u>**weakly-supervised**</u> 使用未标注的数据提升模型性能   

![](Figures/image.png)
这个框架有两个阶段，分别是通过SSM对高一致性样本进行伪标注阶段和通过AL选择低一致性样本阶段。首先使用已标注的图片对模型进行fine-tune，对未标注或部分标注的图片提取region proposals（未标注样本），把这些 **region proposals <u>粘贴</u> 到已标注的图片中进行交叉图片验证，根据重新预测出来的置信度确定如何对未标注样本进行标注** 。对于高一致性样本，直接进行伪标注，对于低一致性样本，通过AL挑选出来，让相关人员进行标注。伪标注的样本用于模型的fine-tune，而新标注的样本添加到已标注的图片中，同时也用于模型的fine-tune  
对于好的样本`xi`，proposal中的内容可以很好的展示j类的特征，粘贴到没有j类的图片中，新生成的图片中的proposal有包含`xi`的proposal，且具有很大的概率值，<u>**高一致性**</u>认为之前的样本框准确无错误➡️正样本
任务分类👇
![](Figures/image%202.png)

---

## Bi-box Regression for Pedestrian Detection and Occlusion Estimation

> Part detector，针对行人遮挡问题，回归「全身」+「可见」两个框  

![](Figures/97B54C4E-F68D-4AB8-B030-A7C87315CE3E.png)
二分支网络：

1. **Full body estimation** 只对pos proposal回归
2. **Visible part estimation** 对pos和neg的proposal回归（FG&BG）， <u>neg proposal回归缩小区域 $\to$ 0</u>
   pos/neg proposal根据和标注(full-body)的IoU决定
   ![](Figures/AFA72E30-3E28-4167-8CC3-28C74B49AA10.png)
   👆proposal由RPN获得，softmax1和softmax2预测行人得分。 <u>fuse</u> 时，两个都为pos，输出p更高；一个为neg，另一分支pos，则pos分支增加p

#### Training

样本标注两个框。把产生的proposal`P={x,y,w,h}`和标注框`Q=(Full,Vis)`match，pos-proposal规则为`IoU(P,F)>thresh_1` && `C(P,V)>thresh_2`. C定义为👇$C(P,\bar{V})=\frac{\text {Area}(P\cap\bar{V})}{\text {Area}(\bar{V})}$

训练样本`X=(Img, P, cate=1, F, V)`，regression target为👇
$\bar{f}^x=\frac{\bar{F}^x-P^x}{P^W},\;\bar{f}^y=\frac{\bar{F}^y-P^y}{P^h}$

$\bar{f}^w=\log(\frac{\bar{F}^w}{P^w}),\;\bar{f}^h=\log(\frac{\bar{F}^h}{P^h})$

Neg-proposal=1.background   2.poorly aligned proposal   回归w,h -> 0

> Why should force _visible part of neg-proposal_ shrink? 「vis分支对pos和neg都处理」 #没懂  
> If the visible part estimation branch is trained to only regress visible parts for positive pedestrian proposals, the training of this branch would be dominated by pedestrian examples which are non-occluded or slightly occluded. For these pedestrian proposals, their ground-truth visible part and full body regions overlap largely. As a result, the estimated visible part region of a negative pedestrian proposal is often close to its estimated full body re- gion and the difference between the two branches after training would not be as large as the case in which the visible part regions of negative examples are forced to shrink to their centers.  

不对负样本处理，则对负样本的预测结果两个分支相同「full分支对所有样本回归到GT，vis分支对正样本回归到GT，对负样本回归到0」
![](Figures/D29D7BC4-9682-4E65-AB16-3A92A974DD47.png)
👆蓝色框，和full(GT)重合度高，但和vis重合度低。在Faster-RCNN中被认为pos，在本文中认为neg。更强的评价标准

---

## Precision Gating: Improving Neural Network Efficiency with Dynamic Dual-Precision Activations

<u>**网络量化**</u>
Network compression: sparsity, quantization, and binarization
使用低精度的浮点运算，相比于静态确定每个weight和activation的精度，本文**根据网络输入**(例如背景不需要精确计算)动态确定 **Tuning the bit width per layer**

#### Precision Gating

> Computes most features with low-precision arithmetic ops and only updates few important features to a high-precision  

1. 对于所有层低精度计算
2. 对于输出的feature map中较大值认为重要特征，对其进行稀疏更新，提高精度(sparse back propagation)

用在shufflenet v2上提升26% ImageNet分类精度

---

## Repulsion Loss: Detecting Pedestrians in a crowd

> ReId的occlude问题，使不同目标的检测框远离「类似triplet loss」  

![](Figures/%E6%88%AA%E5%B1%8F2020-02-23%E4%B8%8A%E5%8D%8812.28.04.png)

$L=L_{Attr}+\alpha*L_{RepGT}+\beta*L_{RepBox}$

#### Attraction term

采用检测框架中bbox回归loss

$L_{\mathrm{Attr}}=\frac{\sum_{P \in \mathcal{P}_{+}} \operatorname{Smooth}_{L 1}\left(P, G_{A t t r}^{P}\right)}{\left|\mathcal{P}_{+}\right|}$

#### Repulsion Term (RepGT)

和周围GT目标框远离，远离IoU大且没有匹配的目标框
即$G_{R e p}^{P}=\underset{G \in \mathcal{G} \backslash\left\{G_{A t r}^{P}\right\}}{\arg \max } \operatorname{IoU}(G, P)$

类似IoU loss（不是IoU而是IoG：若最小化IoU，则预测框越大IoU越小）

$\operatorname{IoG}(P,G) \overset{\triangle}{=}\frac{area(P\cap G)}{area(G)}$

$L_{\mathrm{RepGT}}=\frac{\sum_{P \in \mathcal{P}_{+}} \operatorname{Smooth}_{ln}\left(\operatorname{IoG}(P, G_{Rep}^{P})\right)}{\left|\mathcal{P}_{+}\right|}$

where

$\operatorname{smooth}_{l n}=\left\{\begin{array}{ll}
{-\ln (1-x)} & {x \leq \sigma} \\
{\frac{x-\sigma}{1-\sigma}-\ln (1-\sigma)} & {x>\sigma}
\end{array}\right.$
使预测框集中在匹配的目标附近，而不会偏移到临近物体

#### Repulsion Term (RepBox)

预测框和其他预测框远离（匹配上不同物体的目标框）
$L_{\mathrm{RepBox}}=\frac{\sum_{i \neq j} \operatorname{Smooth}_{l n}\left(\operatorname{IoU}\left(B^{P_{i}}, B^{P_{j}}\right)\right)}{\sum_{i \neq j} \mathbb{1}\left[\operatorname{IoU}\left(B^{P_{i}}, B^{P_{j}}\right)>0\right]+\epsilon}$

防止不同物体的两个检测框被NMS过滤掉

---

## Normalization

![](Figures/2020-02-24-16-07-43-image.png)

#### Training

Batch Norm对一个batch中所有样本的同一channel计算统计量，受batch_size影响

Layer Norm对单个样本计算统计量，用于RNN

Instance Norm单样本单通道计算，风格迁移

Group Norm对通道分组，解决BN依赖batch_size的问题

Switchable Normalization计算BN、LN、IN三种的统计量，然后加权$w_k$作为SN的均值$\mu$和方差$\sigma$「解决batch_size影响，自适应不同任务」

norm👇

$\hat{h}_{n c i j}=\gamma \frac{h_{n c i j}-\Sigma_{k \in \Omega} w_{k} \mu_{k}}{\sqrt{\Sigma_{k \in \Omega} w_{k}^{\prime} \sigma_{k}^{2}+\epsilon}}+\beta$

加权权重归一化👇

$w_k=\frac{e^{\lambda_k}}{\sum_{z\in\{\text {bn,ln,in}\}}e^{\lambda_z}}$

![](Figures/2020-02-24-16-22-39-image.png)

#### Testing

LN, IN正常计算，BN采用<u>batch average</u>方式，具体过程是，冻结所有的参数，从训练集中随机抽取一定数量的样本，计算SN的均值和方差，然后使用他们的平均值作为BN的统计值

Ref: [https://zhuanlan.zhihu.com/p/39296570](https://zhuanlan.zhihu.com/p/39296570)

---

## Universal-RCNN: Universal Object Detection via Transferable Graph R-CNN

> 解决检测域迁移，不同域<u>**类别**</u>关系推理()reasoning)和迁移(transfer)

**Intra-Domain Reasoning**: 域内部图表示上传播，类别之间相关性

**Inter-Graph Transfer**: 域间迁移，不同域类别之间层次关系

![](Figures/2020-02-25-20-41-49-image.png)

#### Intra-Domain Reasoning Module

1. 使用backbone计算proposal feature (global **semantic pool**)

2. 构建**区域**关系图$G_{T\to T}$，节点表示region proposal，边表示关系。proposal之间关联关系(attribute similarities, interactions)

3. 学习边权重$\mathbf{Z}\mathbf{Z}^T$，只保留重要proposal关系的**稀疏邻接矩阵**

4. propsoal feature在GCN计算，和原始特征concat，得到新的global semantic pool $\mathbf{P_S}$

sharing common features between categories via connected edges such as similar attributes & relations.

improve feature rep. by adding adaptive contexts from global semantic pool

#### Inter-Domain Transfer Module

> bridge the gap between domains

源域用上述模块构建$\mathbf{P_S}$，构建$\mathbf{G_{S\to T}}$，GCN计算从源域到目标域迁移，concat源域特征

![](Figures/2020-02-25-22-03-19-image.png)
