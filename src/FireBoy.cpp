#include "FireBoy.hpp"
#include "Util/Image.hpp"

FireBoy::FireBoy() {
  SetImage(GA_RESOURCE_DIR "/Fire/boy/boy_1.png");
  m_Transform.scale = {0.4, 0.4f};
  SetVisible(true);
  SetZIndex(100);
  ResetPosition();
}
void FireBoy::MoveLeft() {
  glm::vec2 newPos = GetPosition();
  newPos.x -= 5.0f;
  SetPosition(newPos);
}

// 向右移動
void FireBoy::MoveRight() {
  glm::vec2 newPos = GetPosition();
  newPos.x += 5.0f;
  SetPosition(newPos);
}
void FireBoy::Jump() {
  if (!isJumping) {    // 只有在地面時才能跳
    velocity.y = 5.0f; // 給一個向上的初速度
    isJumping = true;
  }
}
void FireBoy::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void FireBoy::Update(float deltaTime) {
  glm::vec2 pos = GetPosition();

  velocity.y += gravity * deltaTime;
  pos.y += velocity.y - 0.2;

  if (pos.y <= groundLevel) {
    pos.y = groundLevel;
    velocity.y = 0;
    isJumping = false;
  }

  SetPosition(pos);
}