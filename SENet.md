# Squeeze-and-Excitation Networks
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
