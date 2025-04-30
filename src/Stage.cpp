#include "Stage.hpp"
#include "NewButton.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>
// int RedDiamondAmount, int WaterDiamondAmount
Stage::Stage() {
  SetImage(GA_RESOURCE_DIR "/stage.png");
  this->RedDiamondAmount = RedDiamondAmount;
  this->WaterDiamondAmount = WaterDiamondAmount;
  SetZIndex(90);
  m_Transform.scale = {0.7, 0.7};
  SetPosition({0, 0});

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

void Stage::Update(int RedDiamondAmount, int WaterDiamondAmount) {
  redGemCount = std::make_shared<Text>(RedDiamondAmount);
  redGemCount->SetPosition({30, 13});
  AddChild(redGemCount);

  blueGemCount = std::make_shared<Text>(WaterDiamondAmount);
  blueGemCount->SetPosition({30, -20});
  AddChild(blueGemCount);

  retryButton->Update();
  menuButton->Update();
};
