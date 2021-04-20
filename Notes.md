# Introduction to Inverse Kinematics

## The End Effector is...
The point where we want to rotate the end of our bone mesh to.

## Kinematics means...
If I have these rotations on my bone then where does the end effector fall (where is the end of my bone mesh)? Given the X find the rotations.

## Inverse Kinematics means...
What rotations are required to transform the end of our bone mesh to a particular position (the end effector). Given the rotations find the X.

## The Difference Between Local and Component Space.
In local space the rotations, of the bones in the pose, are assumed to be relative to their parent bone. In component space their position is assumed to be relative to the root of the entire skeletal mesh.

## An Effector is...
A force that is applied to the outside of a joint between two bones in order to cause it to bend at the joint. Think of something pulling on your elbow as an example.

## The Joint Target would be...
The joint to which the effector is applied.

## The IKBone is...
The bone you are wanting to move to the target position.
