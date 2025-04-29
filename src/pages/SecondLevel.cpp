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
  // watergirl(終點比較上面) fireboy
  //-256 -174
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-50, -256));
  m_Root.AddChild(fireboy);
  Girl = std::make_shared<NewWaterGirl>(glm::vec2(-100, 70));
  m_Root.AddChild(Girl);

  Rock = std::make_shared<NewRock>(glm::vec2(-200, 80), glm::vec2(10, 14));
  m_Root.AddChild(Rock);

  Pools.push_back(std::make_shared<NewPool>(glm::vec2(20, -292),
                                            glm::vec2(30, -7), "water"));
  Pools.push_back(std::make_shared<NewPool>(glm::vec2(150, -292),
                                            glm::vec2(30, -7), "fire"));

  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(-340, -26), glm::vec2(20, 2), "blue", -90));
  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(340, 58), glm::vec2(16, 16), "purple", -30));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, -115), glm::vec2(20, 5), "blue", false)); // lever

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(200, -32), glm::vec2(5, 7), "purple", true));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(250, 74), glm::vec2(5, 7), "purple", true));

  for (auto &pool : Pools) {
    m_Root.AddChild(pool);
  }
  for (auto &s : switches) {
    m_Root.AddChild(s);
  }
  for (auto &e : elevators) {
    m_Root.AddChild(e);
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
  Girl->SetElevators(elevators);
  Girl->SetPool(Pools);
  Girl->SetRock(Rock);
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
          anyButtonPressed = true;
          allButtonReleased = false;
        }
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
  Rock->Update(fireboy, Girl);

  m_Root.Update();
};

void SecondLevel::End(){};