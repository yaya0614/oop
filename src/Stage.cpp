#include "Stage.hpp"
#include "NewButton.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>

Stage::Stage(std::string path) {

  this->path = path;
  SetImage(GA_RESOURCE_DIR "/" + path + ".png");
  SetZIndex(90);
  m_Transform.scale = {0.7, 0.7};
  SetPosition({0, 0});

  InitializeButtons(path);
}

void Stage::InitializeButtons(const std::string &path) {
  if (path == "stage_over") {
    retryButton = std::make_shared<NewButton>(glm::vec2(0, -10), "RetryLevel");
    menuButton = std::make_shared<NewButton>(glm::vec2(0, -70), "BackToMenu");
  } else {
    retryButton = std::make_shared<NewButton>(glm::vec2(0, 70), "retry");
    menuButton = std::make_shared<NewButton>(glm::vec2(0, -70), "Next");
  }

  AddChild(retryButton);
  AddChild(menuButton);
}

void Stage::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};

void Stage::Update(int RedDiamondAmount, int WaterDiamondAmount) {
  if (path != "stage_over") {
    LOG_DEBUG("有進來");
    LOG_DEBUG("RedDiamondAmount");
    LOG_DEBUG(RedDiamondAmount);
    redGemCount = std::make_shared<Text>(RedDiamondAmount);
    redGemCount->SetPosition({30, 13});
    AddChild(redGemCount);

    blueGemCount = std::make_shared<Text>(WaterDiamondAmount);
    blueGemCount->SetPosition({30, -20});
    AddChild(blueGemCount);
  }

  retryButton->Update();
  menuButton->Update();
};
