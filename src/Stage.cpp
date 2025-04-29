#include "Stage.hpp"
#include "NewButton.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <memory>
Stage::Stage() {
  SetImage(GA_RESOURCE_DIR "/StageUi.png");
  // SetVisible(true);
  SetZIndex(90);
  m_Transform.scale = {0.7, 0.7};
  SetPosition({0, 0});

  // button = std::make_shared<NewButton>(glm::vec2(0, 0), "main");

  retryButton = std::make_shared<NewButton>(glm::vec2(0, 70), "retry");
  AddChild(retryButton);

  // Menu 按鈕
  menuButton = std::make_shared<NewButton>(glm::vec2(0, -70), "main");

  AddChild(menuButton);
};

void Stage::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};

void Stage::Update() {

  retryButton->Update();
  menuButton->Update();
};
