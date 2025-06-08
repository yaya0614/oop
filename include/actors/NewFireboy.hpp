#pragma once
#include "NewCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "actors/NewRock.hpp"
#include "machines/NewBridge.hpp"
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
  std::vector<std::shared_ptr<NewBridge>> bridges;
  std::vector<std::shared_ptr<NewPool>> pools;

public:
  NewFireBoy(glm::vec2 startPos) : NewCharacter(startPos, "fire", -4) {

    m_Drawable = std::make_shared<Util::Image>(
        "/Users/mel/Desktop/oop/Resources/Rock.png");
    SetVisible(true);
    SetZIndex(60);
    m_Transform.scale = {0.34, 0.34};
    SetPosition(startPos);
    AddChild(boxImage);
  }

  void SetDoor(const std::vector<std::shared_ptr<NewDoor>> &door) {
    doors = door;
  };
  void SetBridge(const std::vector<std::shared_ptr<NewBridge>> &bridge) {
    bridges = bridge;
  }

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
      m_Drawable = std::make_shared<Util::Image>(
          "/Users/mel/Desktop/oop/Resources/s-1.png");

    } else if (status == "InDoor") {
      LOG_ERROR("開完!");
      SetVisible(false);
    }
  };
  void Update(float deltaTime,
              const std::vector<MapBackground::Platform> &platforms) {
    if ((status == "InDoor" || status == "Die") ||
        status == "OtherDie") { // 如果進門裡或是死掉，角色就不能再移動了!!!!
      return;
    }
    bool onElevator = false;
    for (auto &ele : elevators) {
      if (ele && ele->IsCharacterOnElevator(shared_from_this())) {
        onElevator = true;
        isOnElevator = true;
        position.y = ele->GetPosition().y + ele->GetSize().y + 30;
        break;
      } else {
        isOnElevator = false;
      }
    }
    // 判斷是否進入河
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
        // LOG_DEBUG("已經站好，還沒開完.....");
        velocity.x = 0;
        velocity.y = 0;
        if (door->GetCurrentAnimation() == 6 && door->GetSelTag() == tag) {
          status = "InDoor";
        }
      }
    }

    ChangeStatus(status);
    if (rocks && rocks->IsCollidingWithCharacter(shared_from_this(), -1)) {
      onRock = true;
    } else {
      onRock = false;
    }

    bool onBridge = false;
    for (auto &bridge : bridges) {
      if (bridge && bridge->IsCollidingWithMachine(shared_from_this())) {
        onBridge = true;
        // LOG_DEBUG("bridge Pos:");
        // LOG_DEBUG(bridge->GetPosition().y);
        // LOG_DEBUG("fireBoy Pos:");
        // LOG_DEBUG(GetPosition().y);
        float bridgeAngle = bridge->GetAngle();
        // LOG_DEBUG(bridgeAngle);
        float safeAngle = glm::radians(30.0f);

        if (std::abs(bridgeAngle) > safeAngle) {

          onBridge = false;
          isJumping = false;
          velocity.y = 0.0f;
        }
      }
    }

    velocity.x = 0.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
      velocity.x -= 80.0f;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
      velocity.x += 80.0f;
    }

    bool justJumped = false;
    if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
      if ((!isJumping && IsOnGround(platforms)) ||
          (!isJumping && isOnElevator) || (!isJumping && onRock) ||
          (!isJumping && onBridge)) {
        Jump();
        justJumped = true;
      }
    }

    if (jumpingBuffer > 0.0f) {
      jumpingBuffer -= deltaTime;
    }

    bool grounded = IsOnGround(platforms);

    if ((grounded || onElevator || onRock || onBridge) && !justJumped) {
      isJumping = false;
      if (velocity.y < 0) {
        velocity.y = 0;
      }
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
    isJumping = false;
  }
};
