#ifndef COLLIDER
#define COLLIDER

#include "MGameObject.hpp"
#include "MapBackground.hpp"
#include <memory>
class Collider : public MGameObject {
public:
  bool IsOverLines(float expect_x, float expect_y,
                   std::shared_ptr<MapBackground> &background);

  // bool IsCollider(float expect_x, float expect_y,
  //                 std::shared_ptr<MapBackground> &background);
  // 如果player跟障礙物有碰撞，jump就要跳上去
  // player max_x, max_y
};
#endif // COLLIDER_HPP