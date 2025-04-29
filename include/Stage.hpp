#ifndef STAGE_HPP
#define STAGE_HPP

#include "MGameObject.hpp"
#include "NewButton.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"

#include <memory>

class Stage : public MGameObject {
public:
  explicit Stage();
  void Update();
  void SetImage(const std::string &ImagePath);

  void SetGemCounts(int blue, int red);
  void SetVisible(bool visible);
  void SetCallback(std::function<void()> retryCb, std::function<void()> menuCb);

private:
  std::shared_ptr<Util::Image> background;

  std::shared_ptr<NewButton> retryButton;
  std::shared_ptr<NewButton> menuButton;

  std::shared_ptr<Util::Image> blueGemIcon;
  std::shared_ptr<Util::Image> redGemIcon;

  std::shared_ptr<Util::Text> blueGemCount;
  std::shared_ptr<Util::Text> redGemCount;

  int blueCount = 0;
  int redCount = 0;
  std::string m_ImagePath;
};

#endif
