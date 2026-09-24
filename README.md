# SO-101 arm robot module for mc_rtc

This package is a robot module for the [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/) control framework for the [SO-101 arms](https://github.com/TheRobotStudio/SO-ARM100).
It allows to load the robot representation in an mc_rtc controller either for simulation or real robot control.

It provides both variants: the follower (default, the gripper version), and the leader (the handle version).

## Dependencies

- [mc_rtc](https://github.com/jrl-umi3218/mc_rtc): the control framework.
- [so101-description](https://github.com/Hugo-L3174/so101_description): the mc_rtc-formatted robot description.

## Building

It is recommended to build and install it using [mc-rtc-superbuild](https://github.com/mc-rtc/mc-rtc-superbuild) but you can also use
```sh
mkdir build
cd build
cmake ..
make
sudo make install
```

## Usage

The desired variant can be loaded in the mc_rtc general config using
```yaml
# For the follower arm
MainRobot: SO101 # or SO101_follower
```
or
```yaml
# For the leader arm
MainRobot: SO101_leader
```

Alternatively it can be loaded in a controller via the controller config file:
```yaml
robots:
  SO-101_leader:
    module: SO101_leader
  SO-101_follower:
    module: SO101 # or SO101_follower
```
or directly loading the robot module:
```cpp
auto rm_leader = mc_rbdyn::RobotLoader::get_robot_module("SO101_leader");
auto rm_follower = mc_rbdyn::RobotLoader::get_robot_module("SO101");
```
