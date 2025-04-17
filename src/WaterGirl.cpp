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
  SetPosition({-370, -223});
}

void WaterGirl::Jump() {
  if (!isJumping) {
    velocity.y = 4.8f; // 設定跳躍初速度
    isJumping = true;
    jumpingBuffer = 0.1f; // 100ms 內不會進入 onPlatform 判定
  }
}
void WaterGirl::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

WaterGirl::BoolandValue
WaterGirl::IfWaterFallFire(std::shared_ptr<MapBackground> &map) {
  float current_fb_x = GetPosition().x;
  float current_fb_y = GetPosition().y - GetHalfHeight();
  bool isTure = false;
  std::string pair_tag;
  float current_fall_down_h;

  for (auto pool : map->GetLevelData(0).pools) {
    bool check_range =
        ((current_fb_x >= pool.x1) && (current_fb_x <= pool.x2)) &&
        (((current_fb_y - pool.y_high) > 0.01 &&
          (current_fb_y - pool.y_high) < 1.5) ||
         (current_fb_y < pool.y_high - 5));

    if (check_range) {
      isTure = true;

      pair_tag = pool.tag;
      current_fall_down_h = pool.expect_fall_down_h;
    }
  }

  if (isTure) {
    return {true, current_fall_down_h, pair_tag};
  }
  return {false, current_fall_down_h, "no"};
};

void WaterGirl::Update(float deltaTime, std::shared_ptr<MapBackground> &map,
                       std::shared_ptr<Elevation> &elevation,
                       std::shared_ptr<ElevationPurple> &elevationResult_purple,
                       std::shared_ptr<Rock> &rock) {
  glm::vec2 pos = GetPosition();
  auto elevationResult = elevation->IsPlayerOnElevation(pos, GetHalfHeight());
  auto elevationResultP =
      elevationResult_purple->IsPlayerOnElevation(pos, GetHalfHeight());
  auto rockResult = rock->IsPlayerOnRock(pos, GetHalfHeight());

  if (jumpingBuffer > 0.0f) {
    jumpingBuffer -= deltaTime;
  }

  velocity.y += gravity * deltaTime;
  pos.y += velocity.y;

  float poss1 = pos.x;
  float test_y = pos.y - GetHalfHeight();

  if (velocity.y > 0.0f) {
    float head_y = pos.y + GetHalfHeight();
    for (const auto &platform : map->GetLevelData(0).platforms) {
      bool isBetweenX = (poss1 >= platform.x1 && poss1 <= platform.x2);
      bool isCloseAbove =
          (head_y >= platform.y_low - 2.0f && head_y <= platform.y_low + 2.0f);
      if (isBetweenX && isCloseAbove) {
        velocity.y = 0.0f;
        LOG_DEBUG(platform.y_low);
        LOG_CRITICAL(platform.y_high);
        pos.y = platform.y_low - 20;
        break;
      }
    }
  }

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
    onPlatform = true;
  }

  else if (rockResult.isOnRock) {
    onRock = true;
    nearestPlatformY = rockResult.rock_top_y + 50;
    onPlatform = true;
  } else if (IfWaterFallFire(map).IsFall) {
    if (wg_tag != IfWaterFallFire(map).pair_tag) {
      IsFallPool = true;

    } else {

      IsFallPool = false;
      groundLevel = IfWaterFallFire(map).current_fall_down_h;

      if (!isJumping && jumpingBuffer <= 0.0f) {
        pos.y = groundLevel;
        velocity.y = 0.0f;
        isJumping = false;
      }
    }

  } else {

    onElevation = false;
    onRock = false;
    for (const auto &platform : map->GetLevelData(0).platforms) {
      if (poss1 >= platform.x1 && poss1 <= platform.x2) {
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
  } else if (pos.y <= groundLevel) {
    pos.y = groundLevel;
    velocity.y = 0.0f;
    isJumping = false;
  }

  SetPosition(pos);
}

void WaterGirl::Die(bool IsOpen) {
  if (IsOpen) {
    SetVisible(false);
  }
  if (IsFallPool) {
    SetImage(GA_RESOURCE_DIR "/Fire/boy/smoke.png");
    SetPosition(GetPosition());
  }
};
