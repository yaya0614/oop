#include "Rock.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>

Rock::Rock() {
  SetImage(GA_RESOURCE_DIR "/Rock.png");
  m_Transform.scale = {0.35, 0.35f};
  SetVisible(true);
  SetZIndex(100);
  SetPosition({-180, 82});
  Rock_y = GetPosition().y + GetHalfHeight();
}
Rock::PlayerCollierData Rock::CheckCollision(glm::vec2 pos, float GetWidth,
                                             float GetHeight) {
  float rock_left = GetPosition().x - GetHalfWidth();
  float rock_right = GetPosition().x + GetHalfWidth();
  float rock_low_y = GetPosition().y - GetHalfHeight();
  float player_low_y = pos.y - GetHeight;
  float player_left_x = pos.x - GetWidth;
  float player_right_x = pos.x + GetWidth;

  bool IsSmaePlatform =
      (6 >= rock_low_y - player_low_y) && (1 <= rock_low_y - player_low_y);

  bool isHorizontalCollision =
      (((player_left_x < rock_left) && (player_right_x > rock_left)) ||
       ((player_right_x > rock_right) && (player_left_x < rock_right)));
  if (isHorizontalCollision && IsSmaePlatform) {
    if ((player_left_x < rock_left) && (player_right_x > rock_left)) {
      return {true, "left"};
    } else {
      return {true, "right"};
    }
  }
  return {false, "none"};
};
void Rock::Update(bool tag_fire, bool tag_water, std::string PushSide_fire,
                  std::string PushSide_water) {
  if (tag_fire) {
    if (PushSide_fire == "left") {
      SetPosition({GetPosition().x + 2, GetPosition().y});
    } else {
      SetPosition({GetPosition().x - 2, GetPosition().y});
    }
  } else if (tag_water) {
    if (PushSide_water == "left") {
      SetPosition({GetPosition().x + 2, GetPosition().y});
    } else {
      SetPosition({GetPosition().x - 2, GetPosition().y});
    }
  }
};

Rock::RockData Rock::IsPlayerOnRock(const glm::vec2 &playerPos,
                                    float HalfHeight) {
  float player_x = playerPos.x;
  float player_y_low = playerPos.y - HalfHeight;
  bool flag = false;
  float rock_x_left = GetPosition().x - GetHalfWidth();
  float rock_x_right = GetPosition().x + GetHalfWidth();

  float rock_y_top = GetPosition().y + GetHalfHeight();

  bool Is_y_match =
      (player_y_low - rock_y_top >= 0.05) && (player_y_low - rock_y_top <= 3);

  if ((player_x >= rock_x_left && player_x <= rock_x_right) && Is_y_match) {
    flag = true;
    LOG_DEBUG("在上面");
    return {flag, rock_y_top};
  }
  return {flag, rock_y_top};
};

void Rock::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
