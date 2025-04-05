#ifndef ELEVATIONPURPLE_HPP
#define ELEVATIONPURPLE_HPP

#include "MGameObject.hpp"
#include <Util/Animation.hpp>
#include <string>

class ElevationPurple : public MGameObject {

public:
  explicit ElevationPurple();
  struct ElevationData {
    bool isOnElevation;
    float elevationY;
  };
  void SetImage(const std::string &ImagePath);
  void Update(float deltaTime, bool IsPressed);
  ElevationData IsPlayerOnElevation(const glm::vec2 &playerPos,
                                    float HalfHeight);

private:
  std::string m_ImagePath;
  std::string init_side = "left";
  float m_TargetY = -28;
  float m_OriginalY = 35;
  float m_Speed = 50.0f;
};
#endif