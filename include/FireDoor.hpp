#ifndef FIREDOOR_HPP
#define FIREDOOR_HPP

#include "MGameObject.hpp"
#include "WaterGirl.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
class FireDoor : public MGameObject {
public:
  explicit FireDoor();
  void SetImage(const std::string &ImagePath);
  bool IsWaterInto(std::shared_ptr<WaterGirl> &watergirl,
                   float GetHalfHeight_w);
  void PlayAnimation();
  void Update(bool tag);
  bool GetIsOpen();

private:
  std::string m_ImagePath;
  bool IsOpen = false;
  const std::vector<std::string> AnimationPaths = {
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_2.png",
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_3.png",
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_4.png",
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_5.png",
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_6.png",
      GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_7.png",
  };
};
#endif