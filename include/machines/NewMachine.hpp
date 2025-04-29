#ifndef NEWMACHINE_HPP
#define NEWMACHINE_HPP

#include "../MGameObject.hpp"
#include "actors/NewCharacter.hpp"
#include <glm/fwd.hpp>
#include <string>

class NewMachine : public MGameObject {
public:
  NewMachine(glm::vec2 startPos, glm::vec2 size, std::string color) {
    this->size = size;
    this->startPos = startPos;
  };

  bool IsCollidingWithMachine(
      std::shared_ptr<NewCharacter> character); // 判斷是否與某個平台相交
  bool IsCharacterOnElevator(std::shared_ptr<NewCharacter> character);

protected:
  bool Activate = false;
  std::string color;
  glm::vec2 startPos;
  glm::vec2 size;
};

#endif
