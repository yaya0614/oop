#ifndef PUSHER_HPP
#define PUSHER_HPP

#include "MGameObject.hpp"
#include "WaterGirl.hpp"
#include <glm/fwd.hpp>

class Pusher : public MGameObject {
public:
  explicit Pusher();
  void SetImage(const std::string &ImagePath);
  void CheckCollision(const std::shared_ptr<WaterGirl> &watergirl,
                      float expect_x,
                      std::shared_ptr<MapBackground> &background, int level_id,
                      int a);

  void CheckCollisionTest(glm::vec2 player, float expect_x,
                          std::shared_ptr<MapBackground> &background,
                          int level_id, int a);
  void Update(float deltaTime);

private:
  std::string m_ImagePath;
  bool m_IsPushed = false; // 是否被按下
  std::string tag = "none";
  float m_TargetY;   // 目標 Y 座標
  float m_OriginalY; // 初始 Y 座標
};
#endif