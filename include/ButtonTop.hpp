#ifndef BUTTONTOP_HPP
#define BUTTONTOP_HPP

#include "MGameObject.hpp"
class ButtonTop : public MGameObject {
public:
  explicit ButtonTop();
  void Update(float deltaTime, bool IsPressed, int WaterGirl_num,
              int FireBoy_num);
  void SetImage(const std::string &ImagePath);

private:
  std::string m_ImagePath;
  int init_sel = 1;
  bool m_IsPressed = false; // 是否被按下
  float m_TargetY;          // 目標 Y 座標
  float m_OriginalY;        // 初始 Y 座標
  float m_Speed = 50.0f;    // 移動速度
};

#endif