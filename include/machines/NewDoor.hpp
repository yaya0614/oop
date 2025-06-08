#ifndef NEWDOOR_HPP
#define NEWDOOR_HPP

#include "Util/Logger.hpp"
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
  void OpenDoor();
  int GetCurrentAnimation();
  std::string GetSelTag() { return self_tag; };
  bool GetIsOpen() { return IsOpen; };
  bool IsCollider(std::shared_ptr<NewCharacter> c1);
  bool IsCharacterMatch(std::shared_ptr<NewCharacter> c1);
  bool IsCharacterInto(std::shared_ptr<NewCharacter> c1,
                       std::shared_ptr<NewCharacter> c2);
  void PlayAnima(std::string fireboy, std::string watergirl) {
    if (fireboy == "InDoor" && watergirl == "InDoor") {
      auto animation = std::make_shared<Util::Animation>(AnimationPaths, false,
                                                         300, false, 0);
      animation->Play();
      SetDrawable(animation);
    }
  };

protected:
  glm::vec2 startpos;
  glm::vec2 size;
  std::string color;
  std::string self_tag;
  bool IsOpen = false;
  std::shared_ptr<Util::Animation> animation; // 加這行

  std::vector<std::string> AnimationPaths;
};
#endif