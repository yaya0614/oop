#include "NewButton.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

NewButton::NewButton(glm::vec2 startpos, std::string imagePath) {
  this->startpos = startpos;
  this->imagePath = imagePath;
  m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/" +
                                             imagePath + "_btn.png");
  SetPosition(startpos);
  SetVisible(true);
  SetZIndex(100); // 確保在 UI 上層
}

void NewButton::SetOnClick(const std::function<void()> &callback) {

  onClick = callback;
}

void NewButton::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  //   LOG_DEBUG(mousePos);
  glm::vec2 pos = GetPosition();
  glm::vec2 size = GetScaledSize();

  bool isInside =
      mousePos.x >= pos.x - size.x / 2 && mousePos.x <= pos.x + size.x / 2 &&
      mousePos.y >= pos.y - size.y / 2 && mousePos.y <= pos.y + size.y / 2;

  bool isPressed = Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB);

  if (isInside) {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/" +
                                               imagePath + "_btn1.png");
    if (isPressed) {
    }

  } else {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/" +
                                               imagePath + "_btn.png");
  }

  wasPressedLastFrame = isPressed;
}
