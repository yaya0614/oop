#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

class BackgroundImage : public Util::GameObject {

public:
  BackgroundImage()
      : GameObject(std::make_unique<Util::Image>(
                       GA_RESOURCE_DIR "/Image/Background/background.png"),
                   -10) {}

  void NextPhase(const int phase) {
    auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
    temp->SetImage(ImagePath(phase));
  }

private:
  inline std::string ImagePath(const int phase) {
    LOG_DEBUG("phase:", phase);
    return GA_RESOURCE_DIR "/Image/Background/Level" +
           std::to_string(phase - 1) + ".png";
  }
};

#endif // BACKGROUND_IMAGE_HPP
