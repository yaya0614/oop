#include "FireBoy.hpp"
#include "Elevation.hpp"
#include "MapBackground.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <glm/fwd.hpp>
#include <memory>

FireBoy::FireBoy() {
  SetImage(GA_RESOURCE_DIR "/Fire/boy/boy_1.png");
  m_Transform.scale = {0.4, 0.4f};
  SetVisible(true);
  SetZIndex(100);
  SetPosition({100, -307});
}

void FireBoy::Jump() {
  if (!isJumping) {
    velocity.y = 5.0f; // 設定跳躍初速度
    isJumping = true;
    jumpingBuffer = 0.1f; // 100ms 內不會進入 onPlatform 判定
  }
}

void FireBoy::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

FireBoy::BoolandValue
FireBoy::IfFireFallIce(std::shared_ptr<MapBackground> &map) {
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

void FireBoy::Update(float deltaTime, std::shared_ptr<MapBackground> &map,
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

  float poss = pos.x + GetHalfWidth() + 2;
  float poss1 = pos.x;
  groundLevel = -270.0f;

  bool onPlatform = false;
  float nearestPlatformY = groundLevel;

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
  } else if (IfFireFallIce(map).IsFall) {
    if (fb_tag != IfFireFallIce(map).pair_tag) { // G掉
      IsFallPool = true;
    } else {
      IsFallPool = false;
      groundLevel = IfFireFallIce(map).current_fall_down_h;
      pos.y = groundLevel;
      isJumping = false;
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

void FireBoy::Die(bool IsOpen) {
  if (IsOpen) {
    SetVisible(false);
  }
  if (IsFallPool) {
    SetImage(GA_RESOURCE_DIR "/Fire/boy/smoke.png");
    SetPosition(GetPosition());
  }
};

// 用不到
void FireBoy::Setter(float new_roundLevel) { groundLevel = new_roundLevel; };
float FireBoy::GetGround() { return groundLevel; };
bool FireBoy::GetJump() { return isJumping; };