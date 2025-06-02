#include "actors/NewWaterGirl.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "actors/NewCharacter.hpp"
#include "actors/NewRock.hpp"
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

  AddChild(boxImage);
}
void NewWaterGirl::Jump() {
  if (!isJumping) {
    velocity.y = jumpSpeed; // 正值 往上
    isJumping = true;
    jumpingBuffer = 0.1f;
  }
}
void NewWaterGirl::SetElevators(
    const std::vector<std::shared_ptr<NewElevator>> &elevatorsList) {
  elevators = elevatorsList;
}
void NewWaterGirl::SetRock(const std::shared_ptr<NewRock> &rock) {
  rocks = rock;
};

void NewWaterGirl::SetDoor(const std::vector<std::shared_ptr<NewDoor>> &door) {
  doors = door;
};

bool NewWaterGirl::IsOnGround(
    const std::vector<MapBackground::Platform> &platforms) {
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

void NewWaterGirl::Update(
    float deltaTime, const std::vector<MapBackground::Platform> &platforms) {
  if ((status == "InDoor" ||
       status == "Die")) { // 如果進門裡或是死掉，角色就不能再移動了!!!!
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
  for (auto &pool : pool) {
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

  velocity.x = 0.0f;
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
    velocity.x -= 80.0f;
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::D))
    velocity.x += 80.0f;

  bool justJumped = false;

  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    if ((!isJumping && (IsOnGround(platforms))) ||
        (!isJumping && isOnElevator) || (!isJumping && onRock)) {
      Jump();
      justJumped = true;
    }
  }

  if (jumpingBuffer > 0.0f) {
    jumpingBuffer -= deltaTime;
  }

  bool grounded = IsOnGround(platforms);

  if ((grounded || onElevator || onRock) && !justJumped) {
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

void NewWaterGirl::OnCollideX(){};

void NewWaterGirl::OnCollideY() {
  velocity.y = 0;
  isJumping = false;
}

void NewWaterGirl::ChangeStatus(std::string status) {
  if (status == "Die") {
    // m_Drawable =
    // std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Fire/boy/smoke.png");
  } else if (status == "InDoor") {
    SetVisible(false);
  }
};
