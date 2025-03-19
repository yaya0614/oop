#ifndef FIRESEA_HPP
#define FIRESEA_HPP

#include "Collider.hpp"
#include "FireBoy.hpp"
#include "MGameObject.hpp"
#include "Util/Animation.hpp"
class FireSea : public MGameObject {

public:
  explicit FireSea();

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
  void SetImage(std::vector<std::string> &AnimationPaths);

  // bool IsPlayerFall(std::shared_ptr<FireBoy> &player);

private:
  const std::vector<std::string> AnimationPaths = {
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_1.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_2.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_3.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_4.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_5.png",
  };
};

#endif