#ifndef COLLIDER
#define COLLIDER

#include "MGameObject.hpp"
#include "MapBackground.hpp"
#include <memory>
class Collider : public MGameObject {
public:
  bool IsOverLines(float expect_x, float expect_y,
                   std::shared_ptr<MapBackground> &background);

  // 要標記障礙物兩者的高度platform_y_height-platform_y_low
  // >20就表示這個是障礙物
  bool IsCollider(float fb_expect_x, float fb_expect_y,
                  std::shared_ptr<MapBackground> &background, int level_id,
                  int a);

  bool IsPlatformOrSlope(float fb_expect_x, float fb_expect_y,
                         std::shared_ptr<MapBackground> &background);

  bool IsPressedButtonbool(float fb_expect_x, float fb_expect_y,
                           std::shared_ptr<MapBackground> &background,
                           int level_id, int a);

  // bool IsCollider(float expect_x, float expect_y,
  //                 std::shared_ptr<MapBackground> &background);
  // 如果player跟障礙物有碰撞，jump就要跳上去
  // player max_x, max_y
};
#endif // COLLIDER_HPP