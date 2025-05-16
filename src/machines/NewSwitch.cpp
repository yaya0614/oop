#include "machines/NewSwitch.hpp"
#include "Util/Logger.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <objc/objc.h>

NewSwitch::NewSwitch(glm::vec2 startpos, glm::vec2 size, std::string color,
                     bool IsButton)
    : NewMachine(startpos, size, color) {
  this->IsButton = IsButton;
  this->color = color;
  if (IsButton) {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/btn_" +
                                               color + ".png");
  } else {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Lever/lever_" +
                                               color + ".png");
  }
  m_Transform.scale = {0.35, 0.33};
  SetPosition(startpos);
  SetZIndex(true);
  SetZIndex(90);
};

void NewSwitch::ActivateElevator(
    float dealtatime, std::vector<std::shared_ptr<NewElevator>> elevators) {
  for (auto ele : elevators) {
    if (color == ele->GetColor()) {
      if (current_lever_dir != 0) { // 有推桿才移動
        ele->UpdateActivate(current_lever_dir, dealtatime);
      }
    }
  }
}
void NewSwitch::UpdateSwitchState(
    std::shared_ptr<NewCharacter> c1, std::shared_ptr<NewCharacter> c2,
    float deltaTime, std::vector<std::shared_ptr<NewElevator>> elevators) {
  bool isColliding = IsCollidingWithMachine(c1) || IsCollidingWithMachine(c2);

  if (IsButton) {
    isPressed = isColliding;

  } else {
    // 拉桿：即時更新 current_lever_dir
    if (isColliding) {

      bool c1_trigger =
          (IsCollidingWithMachine(c1) && (c1->dir_out != current_lever_dir));
      bool c2_trigger =
          (IsCollidingWithMachine(c2) && (c2->dir_out != current_lever_dir));

      if (c1_trigger || c2_trigger) {
        current_lever_dir = (c1_trigger) ? c1->dir_out : c2->dir_out;
        ChangeLeverImage(current_lever_dir);
      }
    }
    ActivateElevator(deltaTime, elevators);
  }
}

bool NewSwitch::IsPressed() const { return isPressed; }

std::string NewSwitch::GetColor() const { return color; }

bool NewSwitch::IsButtonType() const { return IsButton; }
void NewSwitch::ButtonPlayAnimation() {
  if (isPressed) {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/btn_" +
                                               color + "1.png");
  } else {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Button/btn_" +
                                               color + ".png");
  }
};
void NewSwitch::ChangeLeverImage(int dir) {

  if (dir < 0) {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Lever/lever_" +
                                               color + "1.png");
  } else {
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Lever/lever_" +
                                               color + ".png");
  }
};
