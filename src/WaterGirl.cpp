#include "WaterGirl.hpp"
#include "Elevation.hpp"
#include "ElevationPurple.hpp"
#include "MapBackground.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>

WaterGirl::WaterGirl() {
  SetImage(GA_RESOURCE_DIR "/IceGirl/girl/girl_1.png");
  m_Transform.scale = {0.4, 0.4f};
  SetVisible(true);
  SetZIndex(100);
  // SetPosition({0, 0});
  SetPosition({-370, -223});
}

void WaterGirl::Jump() {
  if (!isJumping) {
    velocity.y = 5.0f; // 設定跳躍初速度
    isJumping = true;
    jumpingBuffer = 0.1f; // 100ms 內不會進入 onPlatform 判定
  }
}
void WaterGirl::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void WaterGirl::Update(
    float deltaTime, std::shared_ptr<MapBackground> &map,
    std::shared_ptr<Elevation> &elevation,
    std::shared_ptr<ElevationPurple> &elevationResult_purple) {
  glm::vec2 pos = GetPosition();
  auto elevationResult = elevation->IsPlayerOnElevation(pos, GetHalfHeight());

  auto elevationResultP =
      elevationResult_purple->IsPlayerOnElevation(pos, GetHalfHeight());

  if (jumpingBuffer > 0.0f) {
    jumpingBuffer -= deltaTime;
  }

  velocity.y += gravity * deltaTime;
  pos.y += velocity.y;

  float poss = pos.x + GetHalfWidth() + 2;
  float test_y = pos.y - GetHalfHeight();

  bool check_init_x =
      (pos.x >= init_stand_platform.x1) && (pos.x <= init_stand_platform.x2);
  bool check_init_y = (test_y - init_stand_platform.y_high > 0.5) &&
                      (test_y - init_stand_platform.y_high < 1);

  if (check_init_y && !check_init_x) {
    groundLevel = -270.0f;
  }

  float nearestPlatformY = groundLevel;
  bool onPlatform = false;

  if (elevationResult.isOnElevation || elevationResultP.isOnElevation) {
    float catch_value = elevationResult.isOnElevation
                            ? elevationResult.elevationY
                            : elevationResultP.elevationY;
    onElevation = true;
    nearestPlatformY = catch_value + 42.0f;
    LOG_DEBUG(nearestPlatformY);

    onPlatform = true;
  } else {
    onElevation = false;

    for (const auto &platform : map->GetLevelData(0).platforms) {
      if (poss >= platform.x1 && poss <= platform.x2) {
        if (pos.y >= platform.y_high - 5.0f &&
            pos.y <= platform.y_high + 5.0f) {
          nearestPlatformY = platform.y_high;
          onPlatform = true;
          break;
        }
      }
    }
  }

  if (onPlatform && jumpingBuffer <= 0.0f) {
    pos.y = nearestPlatformY;
    velocity.y = 0.0f;
    isJumping = false;
    // LOG_DEBUG(onElevation ? "我在電梯" : "我在平台");
  } else if (pos.y <= groundLevel) {
    pos.y = groundLevel;
    velocity.y = 0.0f;
    isJumping = false;
    // LOG_DEBUG("我在地板");
  }

  SetPosition(pos);
}
