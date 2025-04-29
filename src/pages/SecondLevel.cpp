#include "pages/SecondLevel.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "WaterGirl.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewRock.hpp"
#include "actors/NewWaterGirl.hpp"
#include "machines/NewDoor.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"
#include "machines/NewSwitch.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

void SecondLevel::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel1.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  stages = std::make_shared<Stage>();

  // watergirl(終點比較上面) fireboy
  //-256 -174
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-50, -256));
  m_Root.AddChild(fireboy);
  // x:-100
  Girl = std::make_shared<NewWaterGirl>(glm::vec2(280, -174));
  m_Root.AddChild(Girl);

  Rock = std::make_shared<NewRock>(glm::vec2(-200, 80), glm::vec2(10, 14));
  m_Root.AddChild(Rock);

  // pools
  Pools.push_back(std::make_shared<NewPool>(glm::vec2(20, -292),
                                            glm::vec2(30, -7), "water"));
  Pools.push_back(std::make_shared<NewPool>(glm::vec2(150, -292),
                                            glm::vec2(30, -7), "fire"));
  // elevatorselevators
  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(-340, -26), glm::vec2(20, 2), "blue", -90));
  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(340, 58), glm::vec2(16, 16), "purple", -30));
  // switchs
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, -115), glm::vec2(20, 5), "blue", false)); // lever

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(200, -32), glm::vec2(5, 7), "purple", true));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(250, 74), glm::vec2(5, 7), "purple", true));

  // doors
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(250, 200),
                                            glm::vec2(30, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(320, 200),
                                            glm::vec2(30, 30), "water"));
  std::vector<glm::vec2> redDiamondPositions = {
      {150, -260},
      {-250, 20},
      {-155, 250},
      {0, 200},

  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {20, -260},
      {132, -18},
      {-350, 190},
      {100, 200},

  };
  for (auto &pos : redDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "fire");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  for (auto &pos : waterDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "water");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
  }
  for (auto &pool : Pools) {
    m_Root.AddChild(pool);
  }
  for (auto &s : switches) {
    m_Root.AddChild(s);
  }
  for (auto &e : elevators) {
    m_Root.AddChild(e);
  }
  for (auto &door : doors) {
    m_Root.AddChild(door);
  }
  mapbackground = std::make_shared<MapBackground>();

  m_CurrentState = State::UPDATE;
};

void SecondLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  // Pool Setting
  for (auto &pool : Pools) {
    if (!pool->IsLooping()) {
      pool->SetLooping(true);
    }
  }

  float deltaTime = 1.0 / 60.0f;
  fireboy->SetElevators(elevators);
  fireboy->SetRock(Rock);
  fireboy->SetPool(Pools);
  fireboy->SetDoor(doors);
  Girl->SetElevators(elevators);
  Girl->SetPool(Pools);
  Girl->SetRock(Rock);
  Girl->SetDoor(doors);

  for (auto door : doors) {
    if (!door->GetIsOpen()) {
      door->IsCharacterInto(fireboy, Girl);
    }
  }
  fireboy->Update(deltaTime, mapbackground->GetLevelData(1).platforms);
  Girl->Update(deltaTime, mapbackground->GetLevelData(1).platforms);

  for (auto s : switches) {
    s->UpdateSwitchState(fireboy, Girl, deltaTime, elevators);
  }
  for (auto ele : elevators) {
    std::string eleColor = ele->GetColor();

    bool anyButtonPressed = false; // 只收集Button
    bool allButtonReleased = true; // 只收集Button
    int lever_dir = 0;             // 只收集Lever

    for (auto s : switches) {
      if (s->GetColor() == eleColor && s->IsButtonType()) {
        if (s->IsPressed()) {
          s->ButtonPlayAnimation();
          anyButtonPressed = true;
          allButtonReleased = false;
        }
        s->ButtonPlayAnimation();
      }
    }

    for (auto s : switches) {
      if (s->GetColor() == eleColor && !s->IsButtonType()) {
        lever_dir = s->GetLeverDir();
      }
    }
    if (anyButtonPressed) {
      ele->UpdateBtnActivate(true, deltaTime);
    } else if (lever_dir != 0) {
      ele->UpdateActivate(lever_dir, deltaTime);
    } else if (allButtonReleased) {
      ele->UpdateBtnActivate(false, deltaTime);
    }
  }

  for (auto &diamond : diamonds) {
    if (!diamond->IsCollected()) {
      diamond->Update(); // ⭐ 加這行來更新閃爍效果
    }
    if (diamond->IsCollected())
      continue;

    if (diamond->tag == "fire" && fireboy->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }

    if (diamond->tag == "water" && Girl->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }
  }
  Rock->Update(fireboy, Girl);
  if ((fireboy->GetStatus() == "InDoor" && Girl->GetStatus() == "InDoor") ||
      (fireboy->GetStatus() == "Die" || Girl->GetStatus() == "Die")) {
    m_Root.AddChild(stages);
  }
  stages->Update();
  m_Root.Update();
};

void SecondLevel::End(){};