# Reactive Interception Via a UR5 Robot Arm

## Introduction 
Reactive interception refers to the ability of a robotic arm to intercept and catch an object that is moving in its workspace. 
This is typically achieved by predicting the trajectory of the object and adjusting the position and orientation of the 
robotic arm to intercept the object at the right time and location.

This project develops a model based pipeline to estimate the dynamics of a moving object (in this case a ball). 
Reactive interception first requires fast and accurate sensing. 
ensure that the robotic arm is able to intercept the object in a timely and reliable manner.
The object's pose is estimated by learning a model of it's dynamics through real world data and use the learnt model to predict the 
objects future poses. A compliant robot control policy is designed to intercept the moving target at the estimated future poses.

## Details

The project comprises the following modules developed over ROS middleware:

Sensing: This done via a ASUS Xtion Pro RGBD camera. The object is first detected
and tracked via OpenCV's framework and the ensuing computed bounding boxes are used to estimate the pose of the object in 3D space using
camera depth data. This has been optimised to run at 40 fps on a Intel I7 PC.

Learning: The depth data is gathered from multiple throws of the object and a model is learnt in real-time using the first few datapoints prior to the object's 
release to estimate where the object is going to intersect with the robot's interception plane.

Interception: An interception plane is defined in front of the robot. The robot arm moves to the predicted interception pose to intercept the moving object.
The controller requires the position of interception and via the inbuilt inverse-kinematics module on the UR5 robot arm, the desired joint angles are computed. 
A fast acting custom PID controller written on the robot's firmware would move the robot to the desired end pose in real time.

## Usage:
1. Set up the ASUS Xtion Pro camera and launch the desired ros drivers.
2. Train a classifier on object and background using HAAR training by OpenCV.
3. Launch disp_cv package under the source files, the package performs detection, tracking and psoe prediction and pose interception computation
4. Launch ur_modern_driver to send data over to the robot where the custom controller would move the robot to the desired end pose.
