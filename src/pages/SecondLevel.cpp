#include "pages/SecondLevel.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "WaterGirl.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewWaterGirl.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewSwitch.hpp"
#include <glm/fwd.hpp>
#include <memory>

void SecondLevel::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel1.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  // watergirl(終點比較上面) fireboy
  //-256
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-50, -95));
  m_Root.AddChild(fireboy);
  Girl = std::make_shared<NewWaterGirl>(glm::vec2(-300, -174));
  m_Root.AddChild(Girl);

  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(-340, -26), glm::vec2(16, 16), "blue", -100));
  elevators.push_back(std::make_shared<NewElevator>(
      glm::vec2(340, 58), glm::vec2(16, 16), "purple", 90));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, -115), glm::vec2(20, 5), "blue", false)); // lever
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-150, -12), glm::vec2(5, 5), "blue", true));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(250, 75), glm::vec2(5, 5), "purple", true));

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
  float deltaTime = 1.0 / 60.0f;

  fireboy->Update(deltaTime, mapbackground->GetLevelData(1).platforms);
  Girl->Update(deltaTime, mapbackground->GetLevelData(1).platforms);
  // 將人物的pos、remider傳到machine裡面
  for (auto s : switches) {
    s->IsCollider(fireboy, Girl, elevators, deltaTime);
  }

  m_Root.Update();
};

void SecondLevel::End(){
    // Implementation here
};