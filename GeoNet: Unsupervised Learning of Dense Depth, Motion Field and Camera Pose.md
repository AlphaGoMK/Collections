# 商汤论文分享会
* depth，camera pose slam，optical flow  
前两静态恢复，光流动态  
两张图 correlation  
相同的texture，临近相同texture  
pipeline  
￼Network Architecture  
![architecture](/Fig/geonet.jpg)  
1. 刚性物体结构  
2. 非刚性运动情况  
network  
* deep map确定静止物体  
* pose net 判断角度变化，对运动物体位置修正  
* resflow光流动态恢复  
