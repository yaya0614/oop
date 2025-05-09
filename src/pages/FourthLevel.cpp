#include "pages/FourthLevel.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
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

void FourthLevel::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel4.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  mapbackground = std::make_shared<MapBackground>();
  // fireboy = std::make_shared<NewFireBoy>(glm::vec2(-160, -244));
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-145, 190));
  m_Root.AddChild(fireboy);
  //   watergirl = std::make_shared<NewWaterGirl>(glm::vec2(160, -244));
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(113, 190));
  m_Root.AddChild(watergirl);

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-200, 170), glm::vec2(45, -7), "fire", glm::vec2(0.75, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(185, 170), glm::vec2(45, -7), "water", glm::vec2(0.75, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(286, -277), glm::vec2(45, -7), "fire", glm::vec2(1.2, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-290, -277), glm::vec2(45, -7), "water", glm::vec2(1.2, 0.36)));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(-34, -225), glm::vec2(14, 2),
                                    "yellow", 30, glm::vec2(0.35, 0.36), "x"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(30, -97), glm::vec2(14, 2),
                                    "green", -34, glm::vec2(0.35, 0.36), "x"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(-34, 20), glm::vec2(14, 2),
                                    "blue", 30, glm::vec2(0.35, 0.36), "x"));

  // doors
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-245, -60),
                                            glm::vec2(0, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(235, -76),
                                            glm::vec2(0, 30), "water"));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-143, -147), glm::vec2(3, 7), "yellow", false)); // lever

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(143, -23), glm::vec2(3, 7), "green", false));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-143, 100), glm::vec2(3, 7), "blue", false));
  for (auto &pool : Pools) {
    m_Root.AddChild(pool);
    stash.push_back(pool);
  }
  for (auto &ele : elevators) {
    m_Root.AddChild(ele);
    stash.push_back(ele);
  }
  for (auto &s : switches) {
    m_Root.AddChild(s);
    stash.push_back(s);
  }
  for (auto &door : doors) {
    m_Root.AddChild(door);
    stash.push_back(door);
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
  stages = std::make_shared<Stage>("stage");
  stages_over = std::make_shared<Stage>("stage_over");

  BasicAddStash();
  m_CurrentState = State::UPDATE;
};

void FourthLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  for (auto door : doors) {
    if (!door->GetIsOpen()) {
      door->IsCharacterInto(fireboy, watergirl);
    }
  }
  watergirl->Update(deltaTime, mapbackground->GetLevelData(3).platforms);
  fireboy->Update(deltaTime, mapbackground->GetLevelData(3).platforms);
  fireboy->SetElevators(elevators);
  watergirl->SetElevators(elevators);
  fireboy->SetDoor(doors);
  watergirl->SetDoor(doors);

  fireboy->SetElevators(elevators);
  watergirl->SetElevators(elevators);
  for (auto pool : Pools) {
    if (!pool->IsLooping()) {
      pool->SetLooping(true);
    }
  }
  for (auto s : switches) {
    s->UpdateSwitchState(fireboy, watergirl, deltaTime, elevators);
  }
  fireboy->SetPool(Pools);
  watergirl->SetPool(Pools);
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
  TriggerStage(counter_fire, counter_water);

  m_Root.Update();
};

void FourthLevel::End(){};