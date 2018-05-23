# Automatic Academic Paper Rating Based on Modularized Hierarchical Convolutional Neural Network  
### Related work:  
* LSTM+linear regression output
* convolutional layer to extract local feature
* 2*conv: encode sentence + encode essay
* attention mechanism

### Motivation:  
* score affected by writing and _title_, _author_, _abstract_, _main_ _context_
* propose task
* modularized hierarchical convolutional nn model
* hierarchical structure from word to sentence  
* parts contribution difference  

### Proposed method:  
1. one hot embedding to dense vector x_i of word  
2. attention based CNN in word to get s_i of sentence  
3. attention based CNN in to encode s_i to m_i of module  
4. title only use aCNN word level to sentence level  
5. author weight average method \gamma_i * a_i --> weight * embedding vec(learned)  
6. module repre aggregate --attention pooling-->paper level repre d --softmax--> probability  

##### details of aCNN:  
1. vec和weight矩阵在element-wise相乘，h(filter size)*k(vec dimension), h vec row concatenation each position generate h*k matrix  
2. relu  activation  
3. 一个filter扫一次全文产生结果为m-h+1（m: vec sequence，h: filter size) * h * k, filter-wise  
4. n filter produce m-h+1 * h * k * n feature maps, column concatenation, c^i(row) repre position i in all feature maps  
5. attention -> contribution of each feature map to form high level repre  
6. <img src="https://latex.codecogs.com/gif.latex?\inline&space;z_i=tanh(\bold{W_c}c^{(i)}&plus;\bold{b_c}))" title="z_i=tanh(\bold{W_c}c^{(i)}+\bold{b_c}))" />  
7. z_i refer to feature at each location i  
8. z_i^T * z_i == constant  
9. u_w learned vec for attention  
10. \alpha for softmax
