#pragma once

#include <mc_rbdyn/RobotModule.h>
#include <mc_rbdyn/RobotModuleMacros.h>
#include <mc_robots/api.h>

namespace mc_robots
{

struct MC_ROBOTS_DLLAPI SO101RobotModule : public mc_rbdyn::RobotModule
{
  SO101RobotModule(const std::string & variant = "follower");
};

} // namespace mc_robots
