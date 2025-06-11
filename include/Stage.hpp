#ifndef STAGE_HPP
#define STAGE_HPP

#include "MGameObject.hpp"
#include "NewButton.hpp"
#include "Text.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"

#include <memory>
#include <string>
#include <vector>

class Stage : public MGameObject {
public:
  // int RedDiamondAmount, int WaterDiamondAmount
  explicit Stage(std::string path);
  void Update(int RedDiamondAmount, int WaterDiamondAmount);
  void SetImage(const std::string &ImagePath);
  void InitializeButtons(const std::string &path);
  void SetGemCounts(int blue, int red);
  void SetVisible(bool visible);
  void SetCallback(std::function<void()> retryCb, std::function<void()> menuCb);
  std::shared_ptr<NewButton> GetRetryButton() { return retryButton; };
  std::shared_ptr<NewButton> GetMainButton() { return menuButton; };
  std::shared_ptr<NewButton> GetRetryLevelButton() { return RetryLevelButton; };
  std::shared_ptr<NewButton> GetBackToMenuButton() { return BackToMenuButton; };

private:
  std::shared_ptr<Util::Image> background;

  std::shared_ptr<NewButton> retryButton;
  std::shared_ptr<NewButton> menuButton;
  std::shared_ptr<NewButton> RetryLevelButton;
  std::shared_ptr<NewButton> BackToMenuButton;

  std::shared_ptr<Text> blueGemCount;
  std::shared_ptr<Text> redGemCount;

  int blueCount = 0;
  int redCount = 0;
  std::string path;
  int RedDiamondAmount;
  int WaterDiamondAmount;
  std::string m_ImagePath;
};

#endif
