#include "Collider.hpp"
#include "FireBoy.hpp"
#include "Util/Logger.hpp"
#include <cstdlib>

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
// 加上 AD 後的值
// bool Collider::IsCollider(float fb_expect_x, float fb_expect_y,
//                           std::shared_ptr<MapBackground> &background,
//                           int level_id, int a) {
//   float fb_right_x = (fb_expect_x + GetHalfWidth());
//   float fb_left_x = (fb_expect_x - GetHalfWidth());
//   float fb_low_y = (fb_expect_y - GetHalfHeight());

//   float platform_left_x =
//   (background->GetLevelData(level_id).platforms[a].x1); float
//   platform_right_x = (background->GetLevelData(level_id).platforms[a].x2);
//   float platform_y_low =
//       (background->GetLevelData(level_id).platforms[a].y_low);

//   if (((fb_left_x < platform_left_x) && (fb_right_x > platform_left_x)) ||
//       ((fb_right_x > platform_right_x) && (fb_left_x < platform_right_x))) {
//     return true;
//   }
//   return false;
// };
bool Collider::IsCollider(float fb_expect_x, float fb_expect_y,
                          std::shared_ptr<MapBackground> &background,
                          int level_id, int a) {
  float fb_right_x = fb_expect_x + GetHalfWidth();
  float fb_left_x = fb_expect_x - GetHalfWidth();
  // float fb_low_y = GetScaledSize().y / 2;
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

  bool isStandingOnPlatform = (t1 < platform_y_high && tt == platform_y_low);

  return isHorizontalCollision && isStandingOnPlatform;
};

bool Collider::IsPressedButtonbool(float fb_expect_x, float fb_expect_y,
                                   std::shared_ptr<MapBackground> &background,
                                   int level_id, int a) {
  float fb_right_x = fb_expect_x + GetHalfWidth() - 10;
  float fb_left_x = fb_expect_x - GetHalfWidth() + 10;

  float tt = GetPosition().y - GetHalfHeight();

  float button_left_x = background->GetLevelData(level_id).buttons[a].x1;
  float button_right_x = background->GetLevelData(level_id).buttons[a].x2;
  float button_y_high = background->GetLevelData(level_id).buttons[a].y_high;

  bool isHorizontalCollision =
      (((fb_left_x < button_left_x) && (fb_right_x > button_left_x)) ||
       ((fb_right_x > button_right_x) && (fb_left_x < button_right_x)));

  bool isStandingOnPlatform = (tt == button_y_high);

  return isHorizontalCollision && isStandingOnPlatform;
};