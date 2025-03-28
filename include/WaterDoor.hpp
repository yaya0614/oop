#ifndef WATERDOOR_HPP
#define WATERDOOR_HPP

#include "FireBoy.hpp"
#include "MGameObject.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
class WaterDoor : public MGameObject {
public:
  explicit WaterDoor();
  void SetImage(const std::string &ImagePath);
  bool IsWaterInto(std::shared_ptr<FireBoy> &fireboy, float GetHalfHeight_w);
  void PlayAnimation();
  void Update(bool tag);
  bool GetIsOpen();

private:
  std::string m_ImagePath;
  bool IsOpen = false;
  const std::vector<std::string> AnimationPaths = {
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_2.png",
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_3.png",
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_4.png",
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_5.png",
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_6.png",
      GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_7.png",
  };
};
#endif