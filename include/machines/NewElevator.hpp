#ifndef NEWELEVATOR_HPP
#define NEWELEVATOR_HPP

#include "NewMachine.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <string>
class NewElevator : public NewMachine {
public:
  NewElevator(glm::vec2 startpos, glm::vec2 size, std::string color,
              int targetpos, glm::vec2 scale, std::string tag);
  std::string GetColor() { return color; };
  glm::vec2 GetSize() { return size; };

  void UpdateBtnActivate(bool Activate, float deltaTime);
  void UpdateActivate(int dir, float deltaTime);
  std::string GetColor() const;

private:
  std::string tag;
  std::string color;
  glm::vec2 size;
  int record_dir = 1;
  float m_TargetY;
  float m_OriginalY;
  float m_TargetX;
  float m_OriginalX;
  float m_Speed = 50.0f;
  float targetY;
};

#endif