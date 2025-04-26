#include "machines/NewMachine.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

bool NewMachine::IsCollidingWithMachine(
    std::shared_ptr<NewCharacter> character) {
  glm::vec2 pos = {character->position.x,
                   character->position.y + character->offest};

  int character_left = pos.x - character->size.x / 2;
  int character_right = pos.x + character->size.x / 2;
  int character_bottom = pos.y - character->size.y / 2;

  return (character_right >= (startPos.x - size.x) &&
          character_left <= (startPos.x + size.x) &&
          character_bottom - (startPos.y - size.y) >= 0.5 &&
          character_bottom - (startPos.y - size.y) <= 2);
}
