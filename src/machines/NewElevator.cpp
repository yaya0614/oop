#include "machines/NewElevator.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "machines/NewMachine.hpp"
#include <memory>

NewElevator::NewElevator(glm::vec2 startpos, glm::vec2 size, std::string color,
                         int targetpos)
    : NewMachine(startpos, size, color) {
  this->color = color;
  m_OriginalY = startpos.y;
  m_TargetY = targetpos;
  m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Elevation/ele_" +
                                             color + ".png");
  SetPosition(startpos);
  SetZIndex(90);
  m_Transform.scale = {0.4, 0.34};
};

void NewElevator::UpdateActivate(int dir, bool Activate, float dealtatime) {
  float currentY = GetPosition().y;
  // LOG_DEBUG(currentY);

  // if (dir != 0) {
  if (dir != record_dir) { // 有推動
    if (dir == 1) {        // 往右推 上升
      targetY = currentY >= m_TargetY ? m_TargetY : m_OriginalY;
    } else { // 下降
      targetY = currentY >= m_TargetY ? m_TargetY : m_OriginalY;
    }
    record_dir = dir;
  }

  if (currentY != targetY) {
    float direction = (targetY < currentY) ? -1.0f : 1.0f;
    float newY = currentY + direction * m_Speed * dealtatime;

    SetPosition({GetPosition().x, newY});
  }
}
