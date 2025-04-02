#include "Button.hpp"
#include "FireBoy.hpp"
#include "Util/Image.hpp"
#include <memory>

Button::Button() {
  SetImage(GA_RESOURCE_DIR "/Button/purple_btn.png");
  // original pos
  // SetPosition({-140, -120});
  m_Transform.scale = {0.4, 0.32f};
  SetPosition({100, -35});

  SetZIndex(25);

  m_OriginalY = GetPosition().y;
  m_TargetY = m_OriginalY - 20;
};
void Button::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};

void Button::Update(float deltaTime, bool IsPressed) {
  float targetY = IsPressed ? m_TargetY : m_OriginalY;
  float currentY = GetPosition().y;

  if (currentY != targetY) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});

    if (IsPressed) {

      SetZIndex(10);
    } else {

      SetZIndex(25);
    }
  }
}

// void Button::CheckCollision(FireBoy &player) {
//   if (player.GetBoundingBox().intersects(GetBoundingBox())) {
//     m_IsPressed = true;
//     m_TargetY = GetPosition().y + 20; // 下降 20 單位
//   }
// }
