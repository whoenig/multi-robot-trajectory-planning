# multi-robot-trajectory-planning

This repository contains code for the following two publications:

W. Hönig, J. A. Preiss, T. K. S. Kumar, G. S. Sukhatme, and N. Ayanian. "Trajectory Planning for Quadrotor Swarms", in IEEE Transactions on Robotics (T-RO), Special Issue Aerial Swarm Robotics, vol. 34, no. 4, pp. 856-869, August 2018. 

and

M. Debord, W. Hönig, and N. Ayanian. "Trajectory Planning for Heterogeneous Robot Teams", in Proc. IEEE/RSJ International Conference on Intelligent Robots and Systems (IROS), Madrid, Spain, October 2018.

The continuous planner is identical to the one used in the IROS paper, while the discrete portion is a re-write using libMultiRobotPlanning.

Currently, this version only supports the 2D case, using (E)CBS as discrete planner.

## Setup


Tested on Ubuntu 18.04.

```
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
./build/libMultiRobotPlanning/ecbs -i examples/ground/test_2_agents.yaml -o examples/ground/output/discreteSchedule.yaml -w 1.1
python3 libMultiRobotPlanning/example/visualize.py examples/ground/test_2_agents.yaml examples/ground/output/discreteSchedule.yaml
````

### Map Conversion

```
./build/tools/map2octomap/map2octomap -m examples/ground/test_2_agents.yaml -o examples/ground/map.bt
./build/tools/octomap2openscad/octomap2openscad -i examples/ground/map.bt -o examples/ground/output/map.scad
openscad -o examples/ground/output/map.stl examples/ground/output/map.scad
(open in meshlab and resave as binary)
```

### Continuous Optimization

```
(open matlab)
(run path_config)
(run smoother)
```

### Temporal stretching

```
python3 tools/scaleTrajectories.py examples/ground/output/pps/ examples/ground/types.yaml examples/ground/test_2_agents.yaml
```