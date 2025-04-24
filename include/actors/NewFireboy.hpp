#pragma once
#include "NewCharacter.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

#include <iostream>

class NewFireBoy : public NewCharacter {
public:
  bool isJumping = false;
  float jumpingBuffer = 0.0f;
  const float gravity = -300.0f;  // 向下重力是負的（越來越小）
  const float jumpSpeed = 200.0f; // 跳起來是正的（速度往上推）
  const float targethigh = 9;

  NewFireBoy(glm::vec2 startPos) : NewCharacter(startPos) {
    m_Drawable =
        std::make_shared<Util::Image>(GA_RESOURCE_DIR "/FireBoy/boy/boy_1.png");
    SetVisible(true);
    SetZIndex(90);

    m_Transform.scale = {0.36, 0.36};
    SetPosition(startPos);
    AddChild(boxImage);
  }
  void Jump() {
    if (!isJumping) {
      velocity.y = jumpSpeed; // 正值 往上
      isJumping = true;
      jumpingBuffer = 0.1f;
    }
  }
  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms) {
    glm::vec2 tag = {position.x, position.y + offest};
    float bottom = tag.y - size.y / 2;
    const float epsilon = 0.9; // 誤差

    for (const auto &p : platforms) {
      LOG_DEBUG(p.x1);
      if (position.x + size.x / 2 >= p.x1 && position.x - size.x / 2 <= p.x2 &&
          bottom - p.y_high >= 1 && bottom - p.y_high <= 2) {
        LOG_DEBUG("我在true");
        return true;
      }
    }
    return false;
  }

  void Update(float deltaTime,
              const std::vector<MapBackground::Platform> &platforms) {

    velocity.x = 0.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
      velocity.x -= 80.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
      velocity.x += 80.0f;

    // 加入保護：這一秒是否剛跳起來
    bool justJumped = false;
    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
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

  virtual void OnCollideX() override {}

  virtual void OnCollideY() override {
    velocity.y = 0;
    isJumping = false; // 重設跳躍狀態
  }
};
