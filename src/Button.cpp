#include "Button.hpp"
#include "FireBoy.hpp"
#include "Util/Image.hpp"
#include <memory>

Button::Button() {
  SetImage(GA_RESOURCE_DIR "/Button/purple_btn.png");
  m_Transform.scale = {0.4, 0.32f};
  SetPosition({-140, -120});
  SetZIndex(25);

  m_OriginalY = GetPosition().y; // 記錄初始 Y 值
  m_TargetY = m_OriginalY - 20;  // 下降 20 單位
};
void Button::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};
void Button::CheckCollision(const std::shared_ptr<FireBoy> &fireBoy,
                            float expect_x, float expect_y,
                            std::shared_ptr<MapBackground> &background,
                            int level_id, int a) {
  bool isPressed =
      fireBoy->IsPressedButtonbool(expect_x, expect_y, background, 0, 0);

  m_IsPressed = isPressed;
}
void Button::Update(float deltaTime) {
  float targetY = m_IsPressed ? m_TargetY : m_OriginalY;
  float currentY = GetPosition().y;

  if (currentY != targetY) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});

    if (m_IsPressed) {

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
