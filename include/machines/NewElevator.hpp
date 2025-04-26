#ifndef NEWELEVATOR_HPP
#define NEWELEVATOR_HPP

#include "NewMachine.hpp"
#include <glm/fwd.hpp>
#include <string>
class NewElevator : public NewMachine {
public:
  NewElevator(glm::vec2 startpos, glm::vec2 size, std::string color,
              int targetpos);
  std::string GetColor() { return color; };
  void UpdateActivate(int dir, bool Activate, float dealtatime);

private:
  std::string color;
  int record_dir = 1;
  float m_TargetY;
  float m_OriginalY;
  float m_Speed = 50.0f;
  float targetY;
};

#endif