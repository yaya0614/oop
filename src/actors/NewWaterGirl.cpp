#include "actors/NewWaterGirl.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "actors/NewCharacter.hpp"
#include <glm/fwd.hpp>

NewWaterGirl::NewWaterGirl(glm::vec2 startPos) : NewCharacter(startPos, -4) {
  m_Drawable =
      std::make_shared<Util::Image>(GA_RESOURCE_DIR "/IceGirl/girl/girl_1.png");
  SetVisible(true);
  SetZIndex(90);

  m_Transform.scale = {0.34, 0.34};
  SetPosition({startPos.x, startPos.y + 3});

  AddChild(boxImage);
}
void NewWaterGirl::Jump() {
  if (!isJumping) {
    velocity.y = jumpSpeed; // 正值 往上
    isJumping = true;
    jumpingBuffer = 0.1f;
  }
}
bool NewWaterGirl::IsOnGround(
    const std::vector<MapBackground::Platform> &platforms) {
  glm::vec2 tag = {position.x, position.y + offest};
  float bottom = tag.y - size.y / 2;
  const float epsilon = 0.9; // 誤差

  for (const auto &p : platforms) {
    if (position.x + size.x / 2 >= p.x1 && position.x - size.x / 2 <= p.x2 &&
        bottom - p.y_high >= 1 && bottom - p.y_high <= 2) {
      return true;
    }
  }
  return false;
}

void NewWaterGirl::Update(
    float deltaTime, const std::vector<MapBackground::Platform> &platforms) {

  velocity.x = 0.0f;
  if (Util::Input::IsKeyPressed(Util::Keycode::A))
    velocity.x -= 80.0f;
  if (Util::Input::IsKeyPressed(Util::Keycode::D))
    velocity.x += 80.0f;

  // 加入保護：這一秒是否剛跳起來
  bool justJumped = false;
  if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
    if (!isJumping && IsOnGround(platforms)) {
      Jump();
      justJumped = true;
    }
  }

  if (jumpingBuffer > 0.0f) {
    jumpingBuffer -= deltaTime;
  }

  bool grounded = IsOnGround(platforms);
  if (grounded && !justJumped) {
    isJumping = false;
    velocity.y = 0;
  } else {
    velocity.y += gravity * deltaTime;
  }

  MoveX(velocity.x * deltaTime, platforms);
  MoveY(velocity.y * deltaTime, platforms);
  SetPosition(position);
  boxImage->SetPosition({position.x, position.y + offest});
}

void NewWaterGirl::OnCollideX(){};

void NewWaterGirl::OnCollideY() {
  velocity.y = 0;
  isJumping = false; // 重設跳躍狀態
}
