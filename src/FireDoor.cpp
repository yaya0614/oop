#include "FireDoor.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
FireDoor::FireDoor() {
  SetImage(GA_RESOURCE_DIR "/DoorAnimation/water_door/w_door_1.png");
  m_Transform.scale = {0.46, 0.5f};
  SetVisible(true);
  SetZIndex(80);
  SetPosition({250, 206});
};
bool FireDoor::IsWaterInto(std::shared_ptr<WaterGirl> &watergirl,
                           float GetHalfHeight_w) {
  float door_left = GetPosition().x - GetHalfWidth();
  float door_right = GetPosition().x + GetHalfWidth();
  float door_y_low = GetPosition().y - GetHalfHeight();
  float water = watergirl->GetPosition().y - GetHalfHeight_w + 4;

  bool IsSameLow = water >= door_y_low;
  if (((watergirl->GetPosition().x >= door_left) &&
       (watergirl->GetPosition().x <= door_right)) &&
      IsSameLow) {
    return true;
  }
  return false;
};

void FireDoor::PlayAnimation() {
  if (!IsOpen) {
    auto animation =
        std::make_shared<Util::Animation>(AnimationPaths, false, 200, false, 0);
    animation->Play();
    SetDrawable(animation);
    IsOpen = true;
  }
};
bool FireDoor::GetIsOpen() { return IsOpen; };

void FireDoor::Update(bool tag) {
  if (tag) {
    PlayAnimation();
  }
};

void FireDoor::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}