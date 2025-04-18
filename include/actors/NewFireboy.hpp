#pragma once
#include "NewCharacter.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"

#include <iostream>

class NewFireBoy : public NewCharacter {
public:
  bool isJumping = false;
  float jumpingBuffer = 0.0f;
  const float gravity = -150.0f;  // 向下重力是負的（越來越小）
  const float jumpSpeed = 200.0f; // 跳起來是正的（速度往上推）
  const int targethigh = 250;

  NewFireBoy(glm::vec2 startPos) : NewCharacter(startPos) {
    m_Drawable =
        std::make_shared<Util::Image>(GA_RESOURCE_DIR "/FireBoy/boy/boy_1.png");
    SetVisible(true);
    SetZIndex(90);

    m_Transform.scale = {0.38, 0.38};
    SetPosition(startPos);
    AddChild(boxImage);
  }
  void Jump() {
    if (!isJumping) {
      velocity.y = jumpSpeed; // 正值：往上
      isJumping = true;
      jumpingBuffer = 0.1f;
    }
  }

  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms) {

    // glm::vec2 testPos = position + glm::vec2(0, 1);
    for (const auto &p : platforms) {
      if (velocity.y < 0) {
        if (IsCollidingWithPlatform(p)) {
          return true;
        }
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

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
      Jump();
    }
    if (isJumping) {
      if (velocity.y) {
      }
      velocity.y += targethigh * deltaTime;
    }

    velocity.y += gravity * deltaTime;

    if (jumpingBuffer > 0.0f) {
      jumpingBuffer -= deltaTime;
    }

    if (jumpingBuffer <= 2.0f && IsOnGround(platforms)) {
      isJumping = false;
      velocity.y = 0;
    }

    MoveX(velocity.x * deltaTime, platforms);
    MoveY(velocity.y * deltaTime, platforms);
    SetPosition(position);
    boxImage->SetPosition({position.x, position.y + offest});
  }

  virtual void OnCollideX() override {
    // std::cout << "[FireBoy] 撞牆啦！X方向" << std::endl;
  }

  virtual void OnCollideY() override {
    // std::cout << "[FireBoy] 落地啦！Y方向" << std::endl;
    velocity.y = 0;
    isJumping = false; // ✨ 重設跳躍狀態
  }
};
