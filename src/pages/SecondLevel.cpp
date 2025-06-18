#include "pages/SecondLevel.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "MapBackground.hpp"
#include "NewButton.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "enum.hpp"
#include "machines/NewBridge.hpp"
#include <codecvt>
#include <glm/fwd.hpp>
#include <memory>

void SecondLevel::Start() {
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Theme.mp3");

  music->SetVolume(60);
  music->Play(-1);
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel2.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);

  bridges.push_back(
      std::make_shared<NewBridge>(glm::vec2(-155, 50), glm::vec2(35, 2),
                                  glm::vec2(0.15, 0.2), "bridge", 85));

  bridges.push_back(
      std::make_shared<NewBridge>(glm::vec2(180, 50), glm::vec2(35, 2),
                                  glm::vec2(0.15, 0.2), "bridge", 85));

  for (auto &b : bridges) {
    m_Root.AddChild(b);
    stash.push_back(b);
  }
  bridge_line.push_back(std::make_shared<NewBridge>(
      glm::vec2(-156, 100), glm::vec2(2, 30), glm::vec2(0.4, 0.4), "line", 55));
  bridge_line.push_back(std::make_shared<NewBridge>(
      glm::vec2(180, 100), glm::vec2(2, 30), glm::vec2(0.4, 0.4), "line", 55));
  for (auto &line : bridge_line) {
    m_Root.AddChild(line);
    stash.push_back(line);
  }

  mapbackground = std::make_shared<MapBackground>();
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-330, -244));
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(-280, -244));

  stages = std::make_shared<Stage>("stage");
  stages_over = std::make_shared<Stage>("stage_over");

  m_Root.AddChild(fireboy);
  m_Root.AddChild(watergirl);
  m_Root.AddChild(Background);

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-160, -216), glm::vec2(55, -7), "fire", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(70, -216), glm::vec2(55, -7), "water", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-160, -277), glm::vec2(55, -7), "water", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(70, -277), glm::vec2(55, -7), "fire", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-152, -17), glm::vec2(70, -9), "green", glm::vec2(0.6, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(182, -17), glm::vec2(80, -9), "green", glm::vec2(0.62, 0.36)));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(120, 163), glm::vec2(34, 5),
                                    "yellow", 15, glm::vec2(0.55, 0.36), "x"));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(170, 197), glm::vec2(-6, 5), "yellow",
      true)); // button(每個switch都要調y的觸發點，才可以準確觸發碰撞項)
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, 197), glm::vec2(-6, 5), "yellow", true)); // button

  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-310, 221),
                                            glm::vec2(5, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-240, 221),
                                            glm::vec2(5, 30), "water"));
  BasicAddStash();

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
  for (auto &s : switches) {
    m_Root.AddChild(s);
    stash.push_back(s);
  }
  for (auto &ele : elevators) {
    m_Root.AddChild(ele);
    stash.push_back(ele);
  }

  for (auto pool : Pools) {
    m_Root.AddChild(pool);
    stash.push_back(pool);
  }
  for (auto door : doors) {
    m_Root.AddChild(door);
    stash.push_back(door);
  }
  RefreshButton = std::make_shared<NewButton>(glm::vec2(350, 250), "Refresh");
  m_Root.AddChild(RefreshButton);
  stash.push_back(RefreshButton);

  ModeButton = std::make_shared<NewButton>(glm::vec2(290, 262), "mode");
  m_Root.AddChild(ModeButton);
  stash.push_back(ModeButton);
  IsModePress = false;

  m_CurrentState = State::UPDATE;
};

void SecondLevel::ResetObject() {
  for (auto item : stash) {
    m_Root.RemoveChild(item);
  }
  RetryAnything();
  stash.clear();
  diamonds.clear();
  doors.clear();
  switches.clear();
  elevators.clear();
  Pools.clear();
  counter_fire = 0;
  counter_water = 0;

  music.reset();
  RefreshButton.reset();
  ModeButton.reset();
  bridges.clear();
  bridge_line.clear();
};

void SecondLevel::Update() {
  ModeButton->Update();
  LOG_DEBUG(IsModePress);
  if (ModeButton->GetIsPressed()) {

    IsModePress = !IsModePress;
  }
  bool someoneDied =
      (fireboy->GetStatus() == "Die" || watergirl->GetStatus() == "Die");

  if (!someoneDied) {
    RefreshButton->Update();

    if (RefreshButton->GetIsPressed()) {
      RetryAnything();
      ResetObject();
      m_CurrentState = State::START;
      return;
    }

    for (auto &pool : Pools) {
      if (!pool->IsLooping()) {
        pool->SetLooping(true);
      }
    }

    if (!IsModePress) {
      fireboy->SetPool(Pools);
      watergirl->SetPool(Pools);
    } else {
      fireboy->SetPool({});
      watergirl->SetPool({});
    }

    fireboy->SetDoor(doors);
    watergirl->SetDoor(doors);

    fireboy->SetElevators(elevators);
    fireboy->SetBridge(bridges);

    watergirl->SetElevators(elevators);
    watergirl->SetBridge(bridges);

    if (!doors[1]->GetIsOpen() || !doors[0]->GetIsOpen()) {
      bool firedoor = (doors[0]->IsCharacterInto(fireboy, watergirl));
      bool waterdoor = (doors[1]->IsCharacterInto(fireboy, watergirl));
      if (firedoor && waterdoor) {
        doors[0]->OpenDoor();
        doors[1]->OpenDoor();
      }
    }

    for (auto &bridge : bridges) {
      bridge->Update(deltaTime, fireboy, watergirl);
    }

    fireboy->Update(deltaTime, mapbackground->GetLevelData(1).platforms);
    watergirl->Update(deltaTime, mapbackground->GetLevelData(1).platforms);

    for (auto s : switches) {
      s->UpdateSwitchState(fireboy, watergirl, deltaTime, elevators);
    }

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
  }

  TriggerBtnOrLever();
  TriggerStage(counter_fire, counter_water, Enum::PhaseEnum::ThirdLevel, stash,
               [this]() { ResetObject(); });

  if (!fireboy || !watergirl) {
    return;
  }
  m_Root.Update();
};

void SecondLevel::End() {
  if (music)
    music->FadeOut(50);
  phase = Enum::PhaseEnum::SecondLevel;
  RetryAnything();
  ResetObject();
  for (auto item : stash) {
    m_Root.RemoveChild(item);
  }
  music.reset();
  m_CurrentState = App::State::START;
};