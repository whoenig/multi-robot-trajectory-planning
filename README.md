# multi-robot-trajectory-planning

This repository contains code for the following two publications:

W. Hönig, J. A. Preiss, T. K. S. Kumar, G. S. Sukhatme, and N. Ayanian. "Trajectory Planning for Quadrotor Swarms", in IEEE Transactions on Robotics (T-RO), Special Issue Aerial Swarm Robotics, vol. 34, no. 4, pp. 856-869, August 2018. 

and

M. Debord, W. Hönig, and N. Ayanian. "Trajectory Planning for Heterogeneous Robot Teams", in Proc. IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS), Madrid, Spain, October 2018.

The continuous planner is identical to the one used in the IROS paper, while the discrete portion is a re-write using libMultiRobotPlanning.

## Setup


Tested on Ubuntu 18.04.

```
cd libMultiRobotPlanning
mkdir build
cd build
cmake ..
make
```

```
cd smoothener
make
Open in matlab
go to external/libsvm/matlab
In Matlab: make
```

## Example

### Discrete Planning

````
./libMultiRobotPlanning/build/ecbs -i examples/ground/test_2_agents.yaml -o examples/ground/output/discreteSchedule.yaml -w 1.1
python3 libMultiRobotPlanning/example/visualize.py examples/ground/test_2_agents.yaml examples/ground/output/discreteSchedule.yaml
````

