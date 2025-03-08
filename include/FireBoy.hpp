#ifndef FIREBOY_HPP
#define FIREBOY_HPP

#include "Collider.hpp"
#include "MGameObject.hpp"
#include "Util/GameObject.hpp"
#include <string>

class FireBoy : public Collider {
public:
  explicit FireBoy();

  void SetImage(const std::string &ImagePath);

  // void ResetPosition() { m_Transform.translation = {0, 0}; }
  void MoveLeft();
  void MoveRight();
  void Jump();
  void Update(float deltaTime); // 更新位置
  void IfOverlines();

  void Setter(float groundLevel);
  float GetGround();
  bool GetJump();

private:
  glm::vec2 velocity = {0.0f, 0.0f}; // 速度 (x, y)
  float gravity = -9.8f;             // 重力加速度
  bool isJumping = false;            // 是否正在跳躍
  float groundLevel = -270.0f;
  std::string m_ImagePath;
};

#endif // FIREBOY_HPP
