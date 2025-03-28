#ifndef ROCK_HPP
#define ROCK_HPP

#include "MGameObject.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
class Rock : public MGameObject {
public:
  explicit Rock();
  struct PlayerCollierData {
    bool tag;
    std::string PushSide;
  };

  struct RockData {
    bool isOnRock;
    float rock_top_y;
  };
  void SetImage(const std::string &ImagePath);

  RockData IsPlayerOnRock(const glm::vec2 &playerPos, float HalfHeight);

  Rock::PlayerCollierData CheckCollision(glm::vec2 pos, float GetWidth,
                                         float GetHeight);
  void Update(bool tag, std::string PushSide);

private:
  float Rock_y;
  std::string m_ImagePath;
};
#endif