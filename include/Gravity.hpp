#include <iostream>
#include <memory>

// 基礎重力類
class Gravity {
protected:
  float gravity = 9.8f;     // 重力加速度
  float velocityY = 0.0f;   // 垂直速度
  float positionY = 500.0f; // 角色當前 Y 軸位置
  float groundY = 100.0f;   // 地板位置（假設地板位於 y=100）
  bool isGrounded = false;  // 是否站在地面上

public:
  virtual void ApplyGravity(float deltaTime) {
    if (!isGrounded) {
      velocityY -= gravity * deltaTime; // 施加重力
    }
  }

  virtual void CheckGroundCollision() {
    if (positionY <= groundY) { // 碰到地板
      positionY = groundY;
      velocityY = 0;
      isGrounded = true;
    } else {
      isGrounded = false;
    }
  }

  virtual void Move(float deltaTime) {
    positionY += velocityY * deltaTime; // 更新位置
  }

  virtual void PrintStatus() {
    std::cout << "Y Position: " << positionY << " | Velocity: " << velocityY
              << " | Grounded: " << (isGrounded ? "Yes" : "No") << std::endl;
  }

  virtual void Jump() {
    if (isGrounded) {
      velocityY = 5.0f; // 跳躍力量
      isGrounded = false;
    }
  }

  virtual ~Gravity() = default;
};