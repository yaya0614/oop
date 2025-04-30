#ifndef NEWDOOR_HPP
#define NEWDOOR_HPP

#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
#include <vector>
class NewDoor : public NewMachine {
public:
  NewDoor(glm::vec2 startpos, glm::vec2 size, std::string color);

  void PlayAnimation();
  bool GetIsOpen() { return IsOpen; };
  bool IsCollider(std::shared_ptr<NewCharacter> c1);
  bool IsCharacterMatch(std::shared_ptr<NewCharacter> c1);
  bool IsCharacterInto(std::shared_ptr<NewCharacter> c1,
                       std::shared_ptr<NewCharacter> c2);

protected:
  glm::vec2 startpos;
  glm::vec2 size;
  std::string color;
  std::string self_tag;
  bool IsOpen = false;
  std::vector<std::string> AnimationPaths;
};
#endif