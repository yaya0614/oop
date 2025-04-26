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
    float dealtatime, bool activate,
    std::vector<std::shared_ptr<NewElevator>> elevators) {
  for (auto ele : elevators) {
    if (color == ele->GetColor()) {
      if (current_lever_dir != 0) { // 有推桿才移動
        ele->UpdateActivate(current_lever_dir, true, dealtatime);
      }
    }
  }
}

void NewSwitch::IsCollider(std::shared_ptr<NewCharacter> character1,
                           std::shared_ptr<NewCharacter> character2,
                           std::vector<std::shared_ptr<NewElevator>> elevators,
                           float dealtatime) {
  if (IsButton) {
    if (IsCollidingWithMachine(character1) ||
        IsCollidingWithMachine(character2)) {
      LOG_DEBUG("有壓到 Button");
      activated = true;
      ChangeButtonImage();
    }
    activated = false;
  } else { // Lever

    bool character1_trigger = (IsCollidingWithMachine(character1) &&
                               (character1->dir_out != current_lever_dir));
    bool character2_trigger = (IsCollidingWithMachine(character2) &&
                               (character2->dir_out != current_lever_dir));

    if (character1_trigger || character2_trigger) {
      current_lever_dir =
          (character1_trigger) ? character1->dir_out : character2->dir_out;
      // LOG_CRITICAL("current_lever_dir");
      // LOG_CRITICAL(current_lever_dir);

      ChangeLeverImage(current_lever_dir);
      activated = true;
    } else {
      activated = false;
    }
  }
  ActivateElevator(dealtatime, activated, elevators);
}

void NewSwitch::ChangeButtonImage() {
  if (activated) {
    SetVisible(false);
  } else {
    SetVisible(true);
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
