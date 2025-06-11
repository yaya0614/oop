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

bool NewMachine::IsCharacterOnElevator(
    std::shared_ptr<NewCharacter> character) {

  float char_left = character->position.x - character->size.x / 2;
  float char_right = character->position.x + character->size.x / 2;
  float char_bottom = character->position.y - character->size.y / 2;

  float ele_left = GetPosition().x - size.x;
  float ele_right = GetPosition().x + size.x;
  float ele_high = GetPosition().y + size.y;

  const float epsilon = 12.0f;

  bool x_overlap = (char_right >= ele_left) && (char_left <= ele_right);

  bool y_touch =
      (char_bottom > ele_high && fabs(char_bottom - ele_high) <= epsilon);
  // LOG_CRITICAL(char_bottom);
  // LOG_CRITICAL(char_bottom);
  // LOG_DEBUG("y_touch");
  // LOG_ERROR(y_touch);
  return x_overlap && y_touch;
}