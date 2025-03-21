#ifndef ELEVATION_HPP
#define ELEVATION_HPP

#include "MGameObject.hpp"
#include <Util/Animation.hpp>

class Elevation : public MGameObject {

public:
  explicit Elevation();
  struct ElevationData {
    bool isOnElevation;
    float elevationY;
  };
  void SetImage(const std::string &ImagePath);
  void Update(float delatime, bool IsPressed);
  ElevationData IsPlayerOnElevation(const glm::vec2 &playerPos,
                                    float HalfHeight);

private:
  std::string m_ImagePath;
  bool init_pressed = false;
  float m_TargetY = -90;
  float m_OriginalY = -28;
  float m_Speed = 50.0f;
};
#endif