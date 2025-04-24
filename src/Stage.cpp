#include "Stage.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <memory>
Stage::Stage() {
  SetImage(GA_RESOURCE_DIR "/StageUi.png");
  SetVisible(true);
  SetZIndex(90);
  m_Transform.scale = {0.7, 0.7};
  SetPosition({0, 0});
};

void Stage::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};