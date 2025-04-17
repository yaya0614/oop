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
  void Update(float delatime, std::string LeftOrRight_fire,
              std::string LeftOrRight_water, bool water_bool, bool fire_bool);

  ElevationData IsPlayerOnElevation(const glm::vec2 &playerPos,
                                    float HalfHeight);

private:
  std::string m_ImagePath;
  std::string init_side = "right";
  std::string recrod_side = "right";
  float m_TargetY = -100;
  float m_OriginalY = -28;
  float m_Speed = 50.0f;
};
#endif