#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Collider.hpp"
#include "FireBoy.hpp"
#include "MGameObject.hpp"

class Button : public MGameObject {
public:
  explicit Button();
  void SetImage(const std::string &ImagePath);
  void CheckCollision(const std::shared_ptr<FireBoy> &fireBoy, float expect_x,
                      float expect_y,
                      std::shared_ptr<MapBackground> &background, int level_id,
                      int a);

  void CheckCollisionTest(const std::shared_ptr<Collider> &player,
                          float expect_x, float expect_y,
                          std::shared_ptr<MapBackground> &background,
                          int level_id, int a);
  void Update(float deltaTime, bool IsPressed);

private:
  std::string m_ImagePath;
  bool m_IsPressed = false; // 是否被按下
  float m_TargetY;          // 目標 Y 座標
  float m_OriginalY;        // 初始 Y 座標
  float m_Speed = 50.0f;    // 移動速度
};
#endif