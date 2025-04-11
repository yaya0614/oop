#include "Diamond.hpp"
#include "Util/Image.hpp"
#include <memory>

Diamond::Diamond(glm::vec2 pos, std::string tag) {
  SetPosition(pos);
  this->tag = tag; // ← 加這行

  if (tag == "fire") {
    m_Drawable =
        std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Dim/red_dim.png");
  } else if (tag == "water") {
    m_Drawable =
        std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Dim/water_dim.png");
  }
  SetVisible(true);
  SetZIndex(90);

  m_Transform.scale = {0.32, 0.32};
  isCollected = false;
}

void Diamond::Collect() {
  isCollected = true;
  SetVisible(false);
}

void Diamond::DisableShow() {
  if (isCollected) {
    SetVisible(false);
  }
};

bool Diamond::IsCollected() const { return isCollected; }
