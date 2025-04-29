#ifndef NEWROCK_HPP
#define NEWROCK_HPP
#include "MapBackground.hpp"
#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <memory>
class NewRock : public NewCharacter {
public:
  NewRock(glm::vec2 startpos, glm::vec2 size);
  bool IsCollidingWithCharacter(std::shared_ptr<NewCharacter> character,
                                int chose); // 判斷是否與某個平台相交

  void Update(std::shared_ptr<NewCharacter> character1,
              std::shared_ptr<NewCharacter> character2);
  void Move(std::shared_ptr<NewCharacter> character);

private:
  glm::vec2 size;
};
#endif