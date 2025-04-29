#ifndef NEWPOOL_HPP
#define NEWPOOL_HPP

#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>
class NewPool : public NewMachine {
public:
  NewPool(glm::vec2 startpos, glm::vec2 size, std::string color);
  bool IsLooping() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
  }

  void SetLooping(bool looping) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetLooping(looping);
    temp->Play();
  }
  std::string IsCharacterFall(std::shared_ptr<NewCharacter> c1);

protected:
  glm::vec2 startpos;
  glm::vec2 size;
  std::string color;
  std::string self_tag;
};
#endif