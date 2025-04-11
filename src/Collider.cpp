#include "Collider.hpp"
#include "FireBoy.hpp"
#include "Util/Logger.hpp"
#include <cstdlib>
#include <string>

bool Collider::IsOverLines(float expect_x, float expect_y,
                           std::shared_ptr<MapBackground> &background) {
  float player_min_x = expect_x - GetScaledSize().x / 2;
  float player_max_x = expect_x + GetScaledSize().x / 2;
  float player_min_y = expect_y - GetScaledSize().y / 2;
  float player_max_y = expect_y + GetScaledSize().y / 2;

  float min_x = background->GetBoundry().min_x;
  float max_x = background->GetBoundry().max_x;
  float min_y = background->GetBoundry().min_y;
  float max_y = background->GetBoundry().max_y;

  if (player_max_x > max_x || player_min_x < min_x || player_max_y > max_y ||
      player_min_y < min_y) {
    return true;
  } else {
    return false;
  }
};
bool Collider::IsCollider(float fb_expect_x, float fb_expect_y,
                          std::shared_ptr<MapBackground> &background,
                          int level_id, int a) {
  float fb_right_x = fb_expect_x + GetHalfWidth();
  float fb_left_x = fb_expect_x - GetHalfWidth();
  float t1 = GetPosition().y;
  float tt = GetPosition().y - GetHalfHeight();

  float platform_left_x = background->GetLevelData(level_id).platforms[a].x1;
  float platform_right_x = background->GetLevelData(level_id).platforms[a].x2;
  float platform_y_high =
      background->GetLevelData(level_id).platforms[a].y_high;
  float platform_y_low = background->GetLevelData(level_id).platforms[a].y_low;

  bool isHorizontalCollision =

      (((fb_left_x < platform_left_x) && (fb_right_x > platform_left_x)) ||
       ((fb_right_x > platform_right_x) && (fb_left_x < platform_right_x)));

  bool isStandingOnPlatform =
      (t1 < platform_y_high && tt - platform_y_low > 0.01 &&
       tt - platform_y_low < 1);

  return isHorizontalCollision && isStandingOnPlatform;
};
Collider::PressedData
Collider::IsPressedButtonbool(float fb_expect_x, float fb_expect_y,
                              std::shared_ptr<MapBackground> &background,
                              int level_id, int a) {
  bool tag = false;
  int num = 100;

  float fb_right_x = fb_expect_x + GetHalfWidth() - 10;
  float fb_left_x = fb_expect_x - GetHalfWidth() + 10;
  float foot_y = fb_expect_y - GetHalfHeight(); // 改用預測位置的 y

  for (int i = 0; i < background->GetLevelData(0).buttons.size(); i++) {
    float button_left_x = background->GetLevelData(0).buttons[i].x1;
    float button_right_x = background->GetLevelData(0).buttons[i].x2;
    float button_y_high = background->GetLevelData(0).buttons[i].y_high;

    bool isHorizontalCollision =
        (((fb_left_x < button_left_x) && (fb_right_x > button_left_x)) ||
         ((fb_right_x > button_right_x) && (fb_left_x < button_right_x)) ||
         (fb_left_x >= button_left_x &&
          fb_right_x <= button_right_x)); // 補中間直接在範圍內

    bool isStandingOnPlatform =
        ((button_y_high - foot_y) >= 0) && ((button_y_high - foot_y) <= 1.5);

    if (isHorizontalCollision && isStandingOnPlatform) {
      tag = true;
      num = i;
    }
  }
  if (tag) {
    return {tag, num};
  } else {
    return {false, 100};
  }

  return {tag, num}; // 沒進 if 就維持預設 false + 100
}

bool Collider::IsCollidingWith(const MGameObject &other) {
  glm::vec2 pos1 = GetPosition();
  glm::vec2 pos2 = other.GetPosition();

  float distance = glm::distance(pos1, pos2);
  return distance < 40.0f;
};
Collider::IsPushedData
Collider::IsPushedbool(float fb_expect_x,
                       std::shared_ptr<MapBackground> &background, int level_id,
                       int a) {

  float p_right_x = fb_expect_x + GetHalfWidth();
  float p_left_x = fb_expect_x - GetHalfWidth();
  float p_bottom_y = GetPosition().y - GetHalfHeight();

  float pusher_left_x = background->GetLevelData(level_id).pushers[a].x1;
  float pusher_right_x = background->GetLevelData(level_id).pushers[a].x2;
  float pusher_y_high = background->GetLevelData(level_id).pushers[a].y_high;

  bool isStandingOnPlatform =
      (p_bottom_y - pusher_y_high >= 0.5) && (p_bottom_y - pusher_y_high <= 2);

  if (isStandingOnPlatform) {

    if (p_right_x > pusher_left_x && p_left_x < pusher_left_x) {
      recent_tag = "right";
      // LOG_DEBUG("1");
      return {true, "right"};
    }

    if (p_left_x < pusher_right_x && p_right_x > pusher_right_x) {
      recent_tag = "left";
      // LOG_DEBUG("2");
      return {true, "left"};
    }
  }
  // LOG_DEBUG("3");
  return {false, recent_tag};
}
