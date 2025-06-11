#include "actors/NewWaterGirl.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "actors/NewCharacter.hpp"
#include "actors/NewRock.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

NewWaterGirl::NewWaterGirl(glm::vec2 startPos)
    : NewCharacter(startPos, "water", -4) {

  m_Drawable =
      std::make_shared<Util::Image>(GA_RESOURCE_DIR "/IceGirl/girl/girl_1.png");
  SetVisible(true);
  SetZIndex(60);
  m_Transform.scale = {0.34, 0.34};
  SetPosition({startPos.x, startPos.y + 3});
}

void NewWaterGirl::Update(
    float deltaTime, const std::vector<MapBackground::Platform> &platforms) {
  if ((status == "InDoor" ||
       status == "Die")) { // 如果進門裡或是死掉，角色就不能再移動了!!!!
    return;
  }
  bool onElevator = false;
  for (auto &ele : elevators) {
    if (!ele)
      continue;

    float eleBottom = ele->GetPosition().y - ele->GetSize().y;
    float eleLeft = ele->GetPosition().x - ele->GetSize().x;
    float eleRight = ele->GetPosition().x + ele->GetSize().x;

    float charTop = position.y + size.y;
    float charBottom = position.y - size.y;
    float charleft = GetPosition().x - size.x / 2;
    float charright = GetPosition().x + size.x / 2;

    bool isHorizontal = (charleft < eleRight && eleLeft < charleft) ||
                        (charright > eleLeft && eleRight > charright);

    if (ele->IsCharacterOnElevator(shared_from_this())) {
      onElevator = true;
      isOnElevator = true;

      position.y = ele->GetPosition().y + ele->GetSize().y + 31;
      break;
    } else {
      isOnElevator = false;
    }

    if (velocity.y > 0 && isHorizontal && charTop <= eleBottom &&
        charTop >= eleBottom - 3.0f) {
      position.y = eleBottom - size.y + 10;
      velocity.y = 0.0f;
    }

    if (!isJumping && (charBottom <= eleBottom && eleBottom <= charTop) &&
        isHorizontal) {

      velocity.x = 0.0f;
      if (position.x < ele->GetPosition().x) {
        position.x = eleLeft - size.x / 2 - 0.1f;
      } else {
        position.x = eleRight + size.x / 2 + 0.1f;
      }
    }
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
  } else {
    onRock = false;
  }

  bool onBridge = false;
  for (auto &bridge : bridges) {
    if (bridge && bridge->IsCollidingWithMachine(shared_from_this())) {
      onBridge = true;

      float bridgeAngle = bridge->GetAngle();
      float safeAngle = glm::radians(30.0f);

      if (std::abs(bridgeAngle) > safeAngle) {

        onBridge = false;
        isJumping = false;
        velocity.y = 0.0f;
      }
    }
  }

  velocity.x = 0.0f;
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    velocity.x -= 80.0f;
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D))
    velocity.x += 80.0f;

  bool justJumped = false;

  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    if ((!isJumping && IsOnGround(platforms)) || (!isJumping && isOnElevator) ||
        (!isJumping && onRock) || (!isJumping && onBridge)) {
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
}

void NewWaterGirl::ChangeStatus(std::string status) {
  if (status == "Die") {
    m_Drawable = std::make_shared<Util::Image>(
        "/Users/mel/Desktop/oop/Resources/s-1.png");

  } else if (status == "OtherDie") {

  } else if (status == "InDoor") {
    SetVisible(false);
  }
};
