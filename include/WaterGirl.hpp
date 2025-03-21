#ifndef WATERGIRL_HPP
#define WATERGIRL_HPP

#include "Collider.hpp"
#include "Elevation.hpp"
#include "ElevationPurple.hpp"
#include "MGameObject.hpp"
#include "MapBackground.hpp"
#include "Util/GameObject.hpp"
#include <imgui.h>
#include <memory>
#include <string>

class WaterGirl : public Collider {
public:
  explicit WaterGirl();

  struct BoolandValue {
    bool IsFall;
    float value;
  };

  struct Platform {
    float x1, x2, y_low, y_high;
  };

  void SetImage(const std::string &ImagePath);

  //   // void ResetPosition() { m_Transform.translation = {0, 0}; }
  void Jump();
  void
  Update(float deltaTime, std::shared_ptr<MapBackground> &map,
         std::shared_ptr<Elevation> &elevation,
         std::shared_ptr<ElevationPurple> &elevationResult_purple); // 更新位置
  void Setter(float groundLevel);
  float GetGround();
  bool GetJump();
  float GetMaxJumpHeight();
  void ResetVelocityY();
  void Die();
  BoolandValue IfFireFallIce(std::shared_ptr<MapBackground> &mpa,
                             float deltaTime);
  glm::vec2 GetVelocity();

private:
  glm::vec2 velocity = {0.0f, 0.0f}; // 速度 (x, y)
  float gravity = -9.8f;             // 重力加速度
  bool isJumping = false;            // 是否正在跳躍
  bool onPlatform = false;
  float groundLevel = -184.0f;
  // float groundLevel = -270.0f;
  std::string m_ImagePath;
  int countD = 0;
  int countA = 0;
  float jumpingBuffer;
  float elevationBuffer = 0.3f;
  bool onElevation = false;

  Platform init_stand_platform = {-401.0f, -142, -199, -224};
};

#endif // WATERGIRL_HPP
