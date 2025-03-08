#include "FireBoy.hpp"
#include "MapBackground.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

FireBoy::FireBoy() {
  SetImage(GA_RESOURCE_DIR "/Fire/boy/boy_1.png");
  m_Transform.scale = {0.4, 0.4f};
  SetVisible(true);
  SetZIndex(100);
  SetPosition({200 + GetWidth(), -380.0f + GetHeight()});
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
  if (!isJumping) {
    velocity.y = 5.0f;
    isJumping = true;
  }
}
void FireBoy::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void FireBoy::Setter(float new_roundLevel) { groundLevel = new_roundLevel; };

float FireBoy::GetGround() { return groundLevel; };

bool FireBoy::GetJump() { return isJumping; };

void FireBoy::Update(float deltaTime) {
  glm::vec2 pos = GetPosition();

  velocity.y += gravity * deltaTime;
  pos.y += velocity.y;

  if (pos.y <= groundLevel) {
    pos.y = groundLevel;
    velocity.y = 0;
    isJumping = false;
  }

  SetPosition(pos);
}
