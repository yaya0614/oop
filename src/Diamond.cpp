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

  m_Transform.scale = {target_size, target_size};
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

void Diamond::Update() {

  scaleTimer += 0.05f;

  if (scaleTimer >= 0.4f) {
    scaleIndex = (scaleIndex + 1) % dim_size.size();
    m_Transform.scale = {dim_size[scaleIndex], dim_size[scaleIndex]};
    scaleTimer = 0.0f; // 重設 timer
  }
};

bool Diamond::IsCollected() const { return isCollected; }