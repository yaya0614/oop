#ifndef FIREBOY_HPP
#define FIREBOY_HPP

#include "MGameObject.hpp"
#include "Util/GameObject.hpp"
#include <string>

class FireBoy : public MGameObject {
public:
  explicit FireBoy();

  void SetImage(const std::string &ImagePath);

  void ResetPosition() { m_Transform.translation = {0, 0}; }
  void MoveLeft();
  void MoveRight();
  void Jump();
  void Update(float deltaTime); // 更新位置
  void IfOverlines();

private:
  glm::vec2 velocity = {0.0f, 0.0f}; // 速度 (x, y)
  float gravity = -9.8f;             // 重力加速度
  bool isJumping = false;            // 是否正在跳躍
  float groundLevel = -200.0f;       // 地面高度

  std::string m_ImagePath;
};

#endif // FIREBOY_HPP
