#pragma once
#include "NewCharacter.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "actors/NewRock.hpp"
#include "machines/NewDoor.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"

#include <memory>
#include <string>
#include <vector>

class NewFireBoy : public NewCharacter,
                   public std::enable_shared_from_this<NewFireBoy> {
private:
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::shared_ptr<NewRock> rocks;
  std::vector<std::shared_ptr<NewPool>> pools;

public:
  NewFireBoy(glm::vec2 startPos) : NewCharacter(startPos, -4) {
    tag = "fire";
    m_Drawable =
        std::make_shared<Util::Image>(GA_RESOURCE_DIR "/FireBoy/boy/boy_1.png");
    SetVisible(true);
    SetZIndex(90);

    m_Transform.scale = {0.34, 0.34};
    SetPosition(startPos);
    AddChild(boxImage);
  }

  void SetDoor(const std::vector<std::shared_ptr<NewDoor>> &door) {
    doors = door;
  };

  void Jump() {
    if (!isJumping) {
      velocity.y = jumpSpeed;
      isJumping = true;
      jumpingBuffer = 0.1f;
    }
  }
  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms) {
    glm::vec2 tag = {position.x, position.y + offest};
    float bottom = tag.y - size.y / 2;

    for (const auto &p : platforms) {
      if (position.x + size.x / 2 >= p.x1 && position.x - size.x / 2 <= p.x2 &&
          bottom - p.y_high >= 1 && bottom - p.y_high <= 2) {
        return true;
      }
    }
    return false;
  }
  void
  SetElevators(const std::vector<std::shared_ptr<NewElevator>> &elevatorsList) {
    elevators = elevatorsList;
  }
  void SetRock(const std::shared_ptr<NewRock> &rock) { rocks = rock; }
  void SetPool(const std::vector<std::shared_ptr<NewPool>> &pool) {
    pools = pool;
  }
  void ChangeStatus(std::string status) {
    if (status == "Die") {
      m_Drawable =
          std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Fire/boy/smoke.png");

    } else if (status == "InDoor") {
      velocity.x = 0;
      velocity.y = 0;
      SetVisible(false);
    }
  };
  void Update(float deltaTime,
              const std::vector<MapBackground::Platform> &platforms) {
    if ((status == "InDoor" || status == "Die")) {
      return;
    }

    for (auto &pool : pools) {

      if (pool && pool->IsCharacterFall(shared_from_this()) != "no") {
        if (pool->IsCharacterFall(shared_from_this()) != tag) {
          status = "Die";
        } else {
          status = "Alive";
        }
      }
    }
    for (auto &door : doors) {
      if (door->GetIsOpen()) {
        if (door->GetCurrentAnimation() == 6 && door->GetSelTag() == tag) {
          status = "InDoor";
        }
      }
    }

    ChangeStatus(status);

    if (rocks && rocks->IsCollidingWithCharacter(shared_from_this(), -1)) {
      onRock = true;
      position.y = rocks->GetPosition().y + 25 + size.y / 2;
      velocity.y = 0.0f;
    } else {
      onRock = false;
    }

    bool onElevator = false;
    for (auto &ele : elevators) {
      if (ele && ele->IsCharacterOnElevator(shared_from_this())) {
        onElevator = true;
        position.y = ele->GetPosition().y + 15 + size.y / 2;
        velocity.y = 0.0f;
        break;
      }
    }

    velocity.x = 0.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
      velocity.x -= 80.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
      velocity.x += 80.0f;

    bool justJumped = false;

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
      // LOG_CRITICAL(onRock);
      if ((!isJumping)) {
        Jump();
        justJumped = true;
      }
      // if ((!isJumping && (IsOnGround(platforms))) ||
      //     (isOnElevator && !isJumping) || (onRock && !isJumping)) {
      //   Jump();
      //   justJumped = true;
      // }
    }

    if (jumpingBuffer > 0.0f) {
      jumpingBuffer -= deltaTime;
    }

    bool grounded = IsOnGround(platforms);

    if ((grounded && !justJumped) || onElevator || onRock) {
      isJumping = false;
      velocity.y = 0;
    } else {
      velocity.y += gravity * deltaTime;
    }

    MoveX(velocity.x * deltaTime, platforms, tag);
    MoveY(velocity.y * deltaTime, platforms);
    SetPosition(position);
    boxImage->SetPosition({position.x, position.y + offest});
  }

  virtual void OnCollideX() override {}

  virtual void OnCollideY() override {
    velocity.y = 0;
    isJumping = false; // 重設跳躍狀態
  }
};
