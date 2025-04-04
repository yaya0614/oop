#include "ElevationPurple.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <memory>
#include <string>

ElevationPurple::ElevationPurple() {
  SetImage(GA_RESOURCE_DIR "/Elevation/ele_purple.png");
  SetPosition({360, 35});

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
  float player_y_low = playerPos.y - HalfHeight;
  bool flag = false;
  int ele_x_left = 312;
  int ele_x_right = 404;
  float ele_y_top = GetPosition().y;

  bool Is_y_match =
      (player_y_low - ele_y_top >= 0.05) && (player_y_low - ele_y_top <= 3);

  if ((player_x >= ele_x_left && player_x <= ele_x_right) && Is_y_match) {
    flag = true;
    return {flag, ele_y_top};
  }
  return {flag, ele_y_top};
};

void ElevationPurple::Update(float deltaTime, bool IsPressed) {

  float targetY = IsPressed ? m_TargetY : m_OriginalY;
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