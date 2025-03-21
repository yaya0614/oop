#include "ElevationPurple.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <memory>
#include <string>

ElevationPurple::ElevationPurple() {
  SetImage(GA_RESOURCE_DIR "/Elevation/ele_purple.png");
  SetPosition({360, 35});
  // SetPosition({-358, -108});

  m_Transform.scale = {0.415, 0.4f};
  SetVisible(true);
  SetZIndex(100);
};

void ElevationPurple::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

ElevationPurple::ElevationData
ElevationPurple::IsPlayerOnElevation(const glm::vec2 &playerPos,
                                     float HalfHeight) {
  float player_x = playerPos.x;
  float player_y_low = playerPos.y - HalfHeight; // Get是拿最下面的y
  bool flag = false;
  int ele_x_left = -400;
  int ele_x_right = -314;
  float ele_y_top = GetPosition().y;
  bool Is_y_match =
      (player_y_low - ele_y_top >= 0.05) && (player_y_low - ele_y_top <= 1);

  if ((player_x >= ele_x_left && player_x <= ele_x_right) && Is_y_match) {
    flag = true;
    return {flag, ele_y_top};
  }
  return {flag, ele_y_top};
};

void ElevationPurple::Update(float deltaTime, std::string LeftOrRight) {
  LOG_DEBUG("LeftOrRight");
  LOG_DEBUG(LeftOrRight);

  float targetY = LeftOrRight == init_side ? m_OriginalY : m_TargetY;
  LOG_INFO("這是targetY");
  LOG_INFO(targetY);

  float currentY = GetPosition().y;

  if (currentY != targetY) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});
  }
}
