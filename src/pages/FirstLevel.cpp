#include "pages/FirstLevel.hpp"
#include "App.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewRock.hpp"
#include "actors/NewWaterGirl.hpp"
#include "enum.hpp"
#include "machines/NewDoor.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"
#include "machines/NewSwitch.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

void FirstLevel::Start() {
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Theme.mp3");

  music->SetVolume(64);
  music->Play(-1);
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel1.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  stages = std::make_shared<Stage>("stage");
  stages_over = std::make_shared<Stage>("stage_over");
  mapbackground = std::make_shared<MapBackground>();

  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-260, -260)); //-254
  m_Root.AddChild(fireboy);

  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(-260, -178)); //-174
  m_Root.AddChild(watergirl);

  Rock = std::make_shared<NewRock>(glm::vec2(-200, 80), glm::vec2(10, 14));
  m_Root.AddChild(Rock);
  stash.push_back(Rock);

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(20, -292), glm::vec2(23, -7), "water", glm::vec2(0.6, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(150, -292), glm::vec2(23, -7), "fire", glm::vec2(0.6, 0.36)));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(-341, -26), glm::vec2(20, 2),
                                    "blue", -90, glm::vec2(0.4, 0.34), "Y"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(340, 56), glm::vec2(22, 2),
                                    "purple", -30, glm::vec2(0.4, 0.34), "Y"));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, -115), glm::vec2(20, 5), "blue", false)); // lever

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(200, -32), glm::vec2(5, 7), "purple", true));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(250, 74), glm::vec2(5, 7), "purple", true));

  doors.push_back(
      std::make_shared<NewDoor>(glm::vec2(250, 200), glm::vec2(0, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(320, 200),
                                            glm::vec2(0, 30), "water"));

  BasicAddStash();
  for (auto &s : switches) {
    m_Root.AddChild(s);
    stash.push_back(s);
  }
  for (auto &e : elevators) {
    m_Root.AddChild(e);
    stash.push_back(e);
  }

  for (auto &pos : redDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "fire");
    diamonds.push_back(diamond);
    stash.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  for (auto &pos : waterDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "water");
    diamonds.push_back(diamond);
    stash.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  for (auto pool : Pools) {
    m_Root.AddChild(pool);
    stash.push_back(pool);
  }
  for (auto door : doors) {
    m_Root.AddChild(door);
    stash.push_back(door);
  }
  m_CurrentState = State::UPDATE;
};

void FirstLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  for (auto &pool : Pools) {
    if (!pool->IsLooping()) {
      pool->SetLooping(true);
    }
  }

  fireboy->SetElevators(elevators);
  fireboy->SetRock(Rock);
  fireboy->SetPool(Pools);
  fireboy->SetDoor(doors);
  watergirl->SetElevators(elevators);
  watergirl->SetPool(Pools);
  watergirl->SetRock(Rock);
  watergirl->SetDoor(doors);

  for (auto door : doors) {
    if (!door->GetIsOpen()) {
      door->IsCharacterInto(fireboy, watergirl);
    }
  }
  fireboy->Update(deltaTime, mapbackground->GetLevelData(0).platforms);
  watergirl->Update(deltaTime, mapbackground->GetLevelData(0).platforms);

  for (auto s : switches) {
    s->UpdateSwitchState(fireboy, watergirl, deltaTime, elevators);
  }
  TriggerBtnOrLever();

  for (auto &diamond : diamonds) {
    if (!diamond->IsCollected()) {
      diamond->Update();
    }
    if (diamond->IsCollected())
      continue;

    if (diamond->tag == "fire" && fireboy->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;

      diamond->DisableShow();
      counter_fire++;
    }

    if (diamond->tag == "water" && watergirl->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
      counter_water++;
    }
  }

  Rock->Update(fireboy, watergirl);

  TriggerStage(counter_fire, counter_water, Enum::PhaseEnum::SecondLevel,
               stash);
  m_Root.Update();
};

void FirstLevel::End() {
  if (music)
    music->FadeOut(50);
  phase = Enum::PhaseEnum::FirstLevel;
  RetryAnything();
  for (auto item : stash) {
    m_Root.RemoveChild(item);
  }
  music.reset();
  m_CurrentState = App::State::START;
};