#ifndef FIREBOY_HPP
#define FIREBOY_HPP

#include "Collider.hpp"
#include "MGameObject.hpp"
#include "MapBackground.hpp"
#include "Util/GameObject.hpp"
#include <imgui.h>
#include <memory>
#include <string>

class FireBoy : public Collider {
public:
  explicit FireBoy();

  struct BoolandValue {
    bool IsFall;
    float current_fall_down_h;
    std::string pair_tag;
  };

  void SetImage(const std::string &ImagePath);

  // void ResetPosition() { m_Transform.translation = {0, 0}; }
  void MoveLeft();
  void MoveRight();
  void Jump();
  void Update(float deltaTime,
              std::shared_ptr<MapBackground> &map); // 更新位置
  void Setter(float groundLevel);
  float GetGround();
  bool GetJump();
  float GetMaxJumpHeight();
  void ResetVelocityY();
  void Die();
  BoolandValue IfFireFallIce(std::shared_ptr<MapBackground> &mpa);
  glm::vec2 GetVelocity();

private:
  glm::vec2 velocity = {0.0f, 0.0f}; // 速度 (x, y)
  float gravity = -9.8f;             // 重力加速度
  bool isJumping = false;            // 是否正在跳躍
  bool onPlatform = false;
  float groundLevel = -270.0f;
  std::string m_ImagePath;
  int countD = 0;
  int countA = 0;
  float jumpingBuffer;
  std::string fb_tag = "fire";
};

#endif // FIREBOY_HPP
