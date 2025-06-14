#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <string>
#include <vector>

#include "MGameObject.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedCharacter : public MGameObject {

public:
  explicit AnimatedCharacter(const std::vector<std::string> &AnimationPaths);

  bool IsLooping() const {

    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
  }

  [[nodiscard]] bool IsPlaying() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() ==
           Util::Animation::State::PLAY;
  }

  void SetLooping(bool looping) {
    auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    temp->SetLooping(looping);
    temp->Play();
  }

  [[nodiscard]] bool IfAnimationEnds() const;
};

#endif // ANIMATED_CHARACTER_HPP
