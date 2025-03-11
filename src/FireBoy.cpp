#include "FireBoy.hpp"
#include "MapBackground.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include <glm/fwd.hpp>

FireBoy::FireBoy() {
  SetImage(GA_RESOURCE_DIR "/Fire/boy/boy_1.png");
  m_Transform.scale = {0.4, 0.4f};
  SetVisible(true);
  SetZIndex(100);
  SetPosition({100, -307});
}
void FireBoy::MoveLeft() {
  glm::vec2 newPos = GetPosition();
  newPos.x -= 5.0f;
  SetPosition(newPos);
}

// 向右移動
void FireBoy::MoveRight() {
  glm::vec2 newPos = GetPosition();
  newPos.x += 5.0f;
  SetPosition(newPos);
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

void FireBoy::Setter(float new_roundLevel) { groundLevel = new_roundLevel; };

float FireBoy::GetGround() { return groundLevel; };

bool FireBoy::GetJump() { return isJumping; };

void FireBoy::Update(float deltaTime, std::shared_ptr<MapBackground> &map) {
  glm::vec2 pos = GetPosition();

  if (jumpingBuffer > 0.0f) {
    jumpingBuffer -= deltaTime;
  }

  velocity.y += gravity * deltaTime;
  pos.y += velocity.y;

  bool onPlatform = false;
  float nearestPlatformY = groundLevel;

  float poss = pos.x + GetHalfWidth() + 2;

  for (const auto &platform : map->GetLevelData(0).platforms) {
    if (poss >= platform.x1 && poss <= platform.x2) {
      if (pos.y >= platform.y_high - 5.0f && pos.y <= platform.y_high + 5.0f) {
        nearestPlatformY = platform.y_high;
        onPlatform = true;
        break;
      }
    }
  }

  if (onPlatform && jumpingBuffer <= 0.0f) {
    pos.y = nearestPlatformY;
    if (velocity.y <= 0.0f) { // 只有當角色正在下落時才停止跳躍
      velocity.y = 0.0f;
      isJumping = false;
    }
  } else if (pos.y <= groundLevel) {
    pos.y = groundLevel;
    velocity.y = 0.0f;
    isJumping = false;
  }

  SetPosition(pos);
}

// void FireBoy::Update(float deltaTime, std::shared_ptr<MapBackground> &map) {
//   glm::vec2 pos = GetPosition();

//   velocity.y += gravity * deltaTime;

//   LOG_DEBUG(velocity.y);
//   pos.y += velocity.y;

//   bool onPlatform = false;
//   float nearestPlatformY = groundLevel;

//   float poss = pos.x + GetHalfWidth() + 2;

//   for (const auto &platform : map->GetLevelData(0).platforms) {
//     if (poss >= platform.x1 && poss <= platform.x2) {
//       if (pos.y >= platform.y_high - 5.0f && pos.y <= platform.y_high + 5.0f)
//       {
//         nearestPlatformY = platform.y_high;
//         onPlatform = true;
//         break;
//       }
//     }
//   }

//   if (onPlatform) {
//     LOG_DEBUG("在平台");
//     pos.y = nearestPlatformY;
//     velocity.y = 0.0f;
//     isJumping = false;
//   } else if (pos.y <= groundLevel) {
//     LOG_DEBUG("在地上");
//     pos.y = groundLevel;
//     velocity.y = 0.0f;
//     isJumping = false;
//   }

//   SetPosition(pos);
// }

// void FireBoy::Update(float deltaTime,
//                      std::shared_ptr<MapBackground> &mapbackground) {
//   float moveSpeed = 2.0f;
//   float expect_x = GetPosition().x;
//   float expect_y = GetPosition().y;

//   // 左右移動
//   if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
//     expect_x += moveSpeed;
//   }
//   if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
//     expect_x -= moveSpeed;
//   }

//   // W鍵：跳躍 + 輕微上升（模擬起跳感）
//   if (Util::Input::IsKeyDown(Util::Keycode::W)) {
//     Jump();
//     // expect_y -= 2.0f;
//   }

//   // 重力計算（更新 Y 軸）
//   // ApplyGravity(deltaTime);
//   expect_y = GetPosition().y;

//   // 加上角色寬度一半（碰撞/位置修正）
//   // glm::vec2 halfSize = GetChracterSize();
//   // expect_x += halfSize.x;

//   // 判斷是否超出邊界或碰撞平台
//   if (!IsOverLines(expect_x, expect_y, mapbackground)) {
//     bool collided = false;
//     for (int i = 0; i < mapbackground->GetLevelData(0).platforms.size(); ++i)
//     {
//       if (IsCollider(expect_x, expect_y, mapbackground, 0, i)) {
//         collided = true;
//         break;
//       }
//     }

//     if (!collided) {
//       SetPosition({expect_x, expect_y}); // 減回去補正
//     }
//   }
// }

float FireBoy::GetMaxJumpHeight() {
  return 50.0f; // 根據遊戲需求調整
}

glm::vec2 FireBoy::GetVelocity() { return velocity; };
void FireBoy::ResetVelocityY() {
  velocity.y = 0;
  isJumping = false;
};
