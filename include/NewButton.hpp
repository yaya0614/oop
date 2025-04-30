#ifndef NEWBUTTON_HPP
#define NEWBUTTON_HPP

#include "MGameObject.hpp"
#include "Util/Image.hpp"

#include <functional>
#include <glm/fwd.hpp>
#include <memory>

class NewButton : public MGameObject {
public:
  NewButton(glm::vec2 startpos, std::string imagePath);

  void SetOnClick(const std::function<void()> &callback);
  void Update();
  std::string GetimagePath() { return imagePath; };
  bool GetIsPressed() { return isPressed; };

private:
  glm::vec2 startpos;
  //   std::shared_ptr<Util::Image> image;
  std::function<void()> onClick;
  std::string imagePath;
  bool isPressed = false;
  bool wasPressedLastFrame = false;
};

#endif
