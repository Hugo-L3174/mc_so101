#include "so101.h"
#include "config.h"

#include <mc_rtc/constants.h>
#include <mc_rtc/logging.h>
#include <RBDyn/parsers/urdf.h>

namespace mc_robots
{

inline static std::string Variant(const std::string & variant)
{
  std::string fullName = "SO101_" + variant;
  return fullName;
}

SO101RobotModule::SO101RobotModule(const std::string & variant)
: RobotModule(mc_rtc::SO101_DESCRIPTION_PATH,
              Variant(variant),
              std::string(mc_rtc::SO101_DESCRIPTION_PATH) + "/urdf/" + Variant(variant) + ".urdf")
{
  mc_rtc::log::success("SO101RobotModule loaded with name: {}", name);
  rsdf_dir = std::string(mc_rtc::SO101_DESCRIPTION_PATH) + "/rsdf";

  mc_rtc::log::success("SO101RobotModule using URDF \"{}\"", urdf_path);
  mc_rtc::log::success("SO101RobotModule using path \"{}\" for rsdf", rsdf_dir);

  // Basic initialization from URDF with fixed base set to true
  init(rbd::parsers::from_urdf_file(urdf_path, true));

  _ref_joint_order = {"shoulder_pan", "shoulder_lift", "elbow_flex", "wrist_flex", "wrist_roll"};

  if(variant == "follower")
  {
    _ref_joint_order.push_back("gripper");
  }
  else
  {
    // @todo find model joint for leader handle
  }

  using namespace mc_rtc::constants;
  _stance["shoulder_pan"] = {0.0};
  _stance["shoulder_lift"] = {0.0};
  _stance["elbow_flex"] = {0.0};
  _stance["wrist_flex"] = {0.0};
  _stance["wrist_roll"] = {0.0};

  if(variant == "leader")
  {
    _stance["gripper"] = {0.0};
  }
  else
  {
    // @todo find model joint for leader handle
  }

  _default_attitude = {{1., 0., 0., 0., 0., 0., 0.}};

  _bodySensors.clear();

  // Add JointSensors for temperature/current logging
  for(size_t i = 0; i < _ref_joint_order.size(); ++i)
  {
    if(mb.jointIndexByName().count(_ref_joint_order[i]) != 0)
    {
      _jointSensors.push_back(mc_rbdyn::JointSensor(_ref_joint_order[i]));
    }
  }

  // Sensors
  // @todo torque sensors from current data ?

  _minimalSelfCollisions = {mc_rbdyn::Collision("base*", "gripper*", 0.02, 0.01, 0.)};
  // @todo add others
  _commonSelfCollisions = _minimalSelfCollisions;
}

} // namespace mc_robots

extern "C"
{
  ROBOT_MODULE_API void MC_RTC_ROBOT_MODULE(std::vector<std::string> & names)
  {
    names = {"SO101", "SO101_leader", "SO101_follower"};
  }
  ROBOT_MODULE_API void destroy(mc_rbdyn::RobotModule * ptr)
  {
    delete ptr;
  }
  ROBOT_MODULE_API mc_rbdyn::RobotModule * create(const std::string & n)
  {
    ROBOT_MODULE_CHECK_VERSION("SO101")
    if(n == "SO101" || n == "SO101_follower")
    {
      return new mc_robots::SO101RobotModule("follower");
    }
    else if(n == "SO101_leader")
    {
      return new mc_robots::SO101RobotModule("leader");
    }
    else
    {
      mc_rtc::log::error("SO101 module cannot create an object of type {}", n);
      return nullptr;
    }
  }
}
