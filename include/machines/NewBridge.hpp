#ifndef NEWBRIDGE_HPP
#define NEWBRIDGE_HPP
#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"
#include <string>
class NewBridge : public NewMachine {
public:
  float angle = 0.0f;       // 目前傾斜角
  float targetAngle = 0.0f; // 目標角
  NewBridge(glm::vec2 startpos, glm::vec2 size, glm::vec2 scale,
            std::string tag, int Zindex);
  void Update(float deltaTime, std::shared_ptr<NewCharacter> c1,
              std::shared_ptr<NewCharacter> c2);

  float GetAngle();
};

#endif