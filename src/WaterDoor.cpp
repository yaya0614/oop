#include "WaterDoor.hpp"
#include "FireBoy.hpp"
#include "Util/Image.hpp"
#include <string>

WaterDoor::WaterDoor() {
  SetImage(GA_RESOURCE_DIR "/DoorAnimation/fire_door/f_door_1.png");
  m_Transform.scale = {0.46, 0.5f};
  SetVisible(true);
  SetZIndex(80);
  SetPosition({320, 206});
}

bool WaterDoor::IsWaterInto(std::shared_ptr<FireBoy> &fireboy,
                            float GetHalfHeight_w) {
  float door_left = GetPosition().x - GetHalfWidth();
  float door_right = GetPosition().x + GetHalfWidth();
  float door_y_low = GetPosition().y - GetHalfHeight();
  float water = fireboy->GetPosition().y - GetHalfHeight_w + 4;

  bool IsSameLow = water >= door_y_low;
  if (((fireboy->GetPosition().x >= door_left) &&
       (fireboy->GetPosition().x <= door_right)) &&
      IsSameLow) {
    return true;
  }
  return false;
};

void WaterDoor::PlayAnimation() {
  if (!IsOpen) {
    auto animation =
        std::make_shared<Util::Animation>(AnimationPaths, false, 200, false, 0);
    animation->Play();
    SetDrawable(animation);
    IsOpen = true;
  }
};
bool WaterDoor::GetIsOpen() { return IsOpen; };

void WaterDoor::Update(bool tag) {
  if (tag) {
    PlayAnimation();
  }
};

void WaterDoor::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}