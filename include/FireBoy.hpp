#ifndef FIREBOY_HPP
#define FIREBOY_HPP

#include "Collider.hpp"
#include "Elevation.hpp"
#include "ElevationPurple.hpp"
#include "MGameObject.hpp"
#include "MapBackground.hpp"
#include "Rock.hpp"
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
  void Jump();
  void Update(float deltaTime, std::shared_ptr<MapBackground> &map,
              std::shared_ptr<Elevation> &elevation,
              std::shared_ptr<ElevationPurple> &elevationResult_purple,
              std::shared_ptr<Rock> &rock); // 更新位置
  // void Update(float deltaTime, std::shared_ptr<MapBackground> &map,
  // std::shared_ptr<Elevation> &elevation); // 更新位置
  void Setter(float groundLevel);
  float GetGround();
  bool GetJump();
  void ResetVelocityY();
  void Die(bool IsOpen);
  BoolandValue IfFireFallIce(std::shared_ptr<MapBackground> &mpa);

private:
  glm::vec2 velocity = {0.0f, 0.0f}; // 速度 (x, y)
  float gravity = -9.8f;             // 重力加速度
  bool isJumping = false;            // 是否正在跳躍
  bool onPlatform = false;
  float groundLevel = -270.0f;
  std::string m_ImagePath;
  float jumpingBuffer;
  std::string fb_tag = "fire";
  float elevationBuffer = 0.3f;
  bool onElevation = false;
  bool onRock = false;
  bool IsFallPool = false;
};

#endif // FIREBOY_HPP
