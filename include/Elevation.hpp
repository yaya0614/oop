#ifndef ELEVATION_HPP
#define ELEVATION_HPP

#include "MGameObject.hpp"
#include <Util/Animation.hpp>

class Elevation : public MGameObject {
public:
  explicit Elevation();
  void SetImage(const std::string &ImagePath);
  void Update(float delatime, bool IsPressed);

private:
  std::string m_ImagePath;
  bool init_pressed = false;
  float m_TargetY = -108;  // 目標 Y 座標
  float m_OriginalY = -28; // 初始 Y 座標
  float m_Speed = 50.0f;   // 移動速度
};
#endif