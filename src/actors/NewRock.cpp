#include "actors/NewRock.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <memory>

NewRock::NewRock(glm::vec2 startpos, glm::vec2 size)
    : NewCharacter(startpos, -4) {
  m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Rock.png");
  SetPosition(startpos);
  m_Transform.scale = {0.3, 0.3};
  SetZIndex(90);
  this->size = size;
};

bool NewRock::IsCollidingWithCharacter(std::shared_ptr<NewCharacter> character,
                                       int chose) {
  glm::vec2 pos = {character->position.x,
                   character->position.y + character->offest};
  int character_left = pos.x - character->size.x / 2;
  int character_right = pos.x + character->size.x / 2;
  int character_bottom = pos.y - character->size.y / 2;

  float rock_left = GetPosition().x - size.x;
  float rock_right = GetPosition().x + size.x;
  float rock_high = GetPosition().y + size.y;
  float rock_bootm = GetPosition().y - size.y;

  const float epsilon = 2.0f; // 允許小誤差（防止浮點數問題）

  // LOG_DEBUG(character_right >= (GetPosition().x - size.x) &&
  // character_left <= (GetPosition().x + size.x));

  if (chose == 1) {
    return (character_right >= (rock_left) && character_left <= (rock_right) &&
            character_bottom - (rock_bootm) >= 0.5 &&
            character_bottom - (rock_bootm) <= 2);
  } else {
    bool x_overlap =
        (character_right >= rock_left) && (character_left <= rock_right);
    bool y_touch = (fabs(character_bottom - rock_high) <= epsilon);
    return x_overlap && y_touch;
  }
}

void NewRock::Move(std::shared_ptr<NewCharacter> character) {
  glm::vec2 RockPos = GetPosition();
  if (character->dir_out == -1) { // 往左拖
    SetPosition({RockPos.x - 2, RockPos.y});
    // LOG_DEBUG("left");
  } else if (character->dir_out == 1) {
    SetPosition({RockPos.x + 2, RockPos.y});
    // LOG_DEBUG("right");
  }
}

void NewRock::Update(std::shared_ptr<NewCharacter> character1,
                     std::shared_ptr<NewCharacter> character2) {
  bool c1 = IsCollidingWithCharacter(character1, 1);
  bool c2 = IsCollidingWithCharacter(character2, 1);
  if (c1 || c2) {
    if (c1) {
      Move(character1);
    } else if (c2) {
      Move(character2);
    }
  }
};