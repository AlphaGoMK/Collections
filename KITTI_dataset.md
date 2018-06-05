# Kitti dataset

* The benchmarks consist of 7481 training images (and point clouds) and 7518 test images (and point clouds)  
* only the classes 'Car' and 'Pedestrian' are evaluated in our benchmark  
* evaluation script will ignore objects detected in don't care regions of the test set.  
* rotation_y is directly given in camera coordinates, while alpha also considers the vector from the camera center to the object center  
* For example, a car which is facing along the X-axis of the camera coordinate system corresponds to rotation_y=0, no matter where it is located in the X/Z plane (bird's eye view), while alpha is zero only, when this object is located along the Z-axis of the camera. When moving the car away from the Z-axis, the observation angle will change.  
* must provide BOTH the 2D 0-based bounding box in the image as well as the 3D bounding box
