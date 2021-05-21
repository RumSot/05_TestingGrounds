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


# TG63 Aiming Our 1st Person Camera.
This lecture is redundant because Unreal 4.19 fixed this problem.
Use Pawn Control Rotation now works whether we are the currently possessed pawn or not; i.e. regardless of whether the camera is in use.


# TG70 Hit vs Overlap Events
The projectile was being destroyed early because we used *OverlapAllDynamic* instead of *Trigger* on both the *LockingTriggerVolume* and *DestroyTriggerVolume*. *OverlapAllDynamic* sets *Projectile* to Block whereas *Trigger* sets it to Ignore!


# TG77 Converting a Character BP to C++
Discovered that *GetActorLocation* does not include the capsule radius. Hence it is necessary to set *Reach Test Includes Agent Radius* and *Reach Test Includes Goal Radius* to false. Otherwise *BTDecorator_IsWithinRange* will conflict with *Move To* in *BT_GuardBehaviour*.


# TG106 Possessing and the View Target
Remember you need to save the Controller when the pawn/actor is possessed so that you can still use after the pawn is unpossesed; we need it in spawn death camera.

When you unpossess an NPC you need to check its controller is valid before you unposses because it may already have been unpossessed.
