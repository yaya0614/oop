#include "machines/NewElevator.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "machines/NewMachine.hpp"
#include <memory>

NewElevator::NewElevator(glm::vec2 startpos, glm::vec2 size, std::string color,
                         int targetpos)
    : NewMachine(startpos, size, color) {
  this->color = color;
  this->size = size;
  m_OriginalY = startpos.y;
  m_TargetY = targetpos;
  m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Elevation/ele_" +
                                             color + ".png");
  SetPosition(startpos);
  SetZIndex(90);
  m_Transform.scale = {0.4, 0.34};
};

void NewElevator::UpdateBtnActivate(bool Activate, float deltaTime) {
  float currentY = GetPosition().y;
  const float epsilon = 0.5f; // 小容忍差距，防止抖動

  // 按鈕壓下 → target是下降的目標
  // 按鈕放開 → target是回到原本高度
  float targetY = Activate ? m_TargetY : m_OriginalY;

  if (fabs(currentY - targetY) > epsilon) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});
  } else {
    // 靠近目標高度就直接貼上去
    SetPosition({GetPosition().x, targetY});
  }
}
void NewElevator::UpdateActivate(int dir, float deltaTime) {
  float currentY = GetPosition().y;
  const float epsilon = 0.5f; // 可接受的小誤差範圍

  if ((dir != record_dir)) {
    if (dir == 1) {
      LOG_DEBUG(1);
      targetY = m_OriginalY;
    } else {
      LOG_DEBUG(2);
      targetY = m_TargetY;
    }
    record_dir = dir;
  }

  if (fabs(currentY - targetY) > epsilon) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});
  } else {
    SetPosition({GetPosition().x, targetY});
  }
}

// void NewElevator::UpdateActivate(int dir, bool dummy, float deltaTime) {
//   float currentY = GetPosition().y;
//   const float epsilon = 0.5f; // 可接受的小誤差範圍

//   if ((dir != record_dir)) {
//     if (dir == 1) {
//       targetY = m_OriginalY;
//     } else {
//       targetY = m_TargetY;
//     }
//     record_dir = dir;
//   }

//   if (fabs(currentY - targetY) > epsilon) {
//     float direction = (targetY > currentY) ? 1.0f : -1.0f;
//     float newY = currentY + direction * m_Speed * deltaTime;

//     if ((direction > 0 && newY > targetY) ||
//         (direction < 0 && newY < targetY)) {
//       newY = targetY;
//     }

//     SetPosition({GetPosition().x, newY});
//   } else {
//     SetPosition({GetPosition().x, targetY});
//   }
// }
