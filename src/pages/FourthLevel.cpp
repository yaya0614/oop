#include "pages/FourthLevel.hpp"
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
void FourthLevel::Start() {
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Theme.mp3");

  music->SetVolume(60);
  music->Play(-1);
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel4.png");
  Background->SetVisible(true);
  Background->SetZIndex(40);
  m_Root.AddChild(Background);
  mapbackground = std::make_shared<MapBackground>();
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-150, -244));
  m_Root.AddChild(fireboy);
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(150, -244));

  m_Root.AddChild(watergirl);

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-200, 170), glm::vec2(45, -8), "fire", glm::vec2(0.75, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(185, 170), glm::vec2(45, -8), "water", glm::vec2(0.75, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(286, -277), glm::vec2(85, -12), "fire", glm::vec2(1.2, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(glm::vec2(-290, -277),
                                            glm::vec2(85, -12), "water",
                                            glm::vec2(1.2, 0.36)));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(-34, -225), glm::vec2(36, 5),
                                    "yellow", 30, glm::vec2(0.35, 0.36), "x"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(30, -99), glm::vec2(39, 5),
                                    "green", -34, glm::vec2(0.35, 0.36), "x"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(-34, 19), glm::vec2(29, 5),
                                    "blue", 30, glm::vec2(0.35, 0.36), "x"));
  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(330, 123), glm::vec2(34, 5),
                                    "orange", -90, glm::vec2(0.4, 0.34), "Y"));

  // doors
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-245, -60),
                                            glm::vec2(5, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(235, -76),
                                            glm::vec2(5, 30), "water"));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-143, -147), glm::vec2(3, 7), "yellow", false)); // lever

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(143, -23), glm::vec2(3, 7), "green", false));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-143, 100), glm::vec2(3, 7), "blue", false));
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-341, -130), glm::vec2(-6, 7), "orange", true));

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
  RefreshButton = std::make_shared<NewButton>(glm::vec2(340, 250), "Refresh");
  ModeButton = std::make_shared<NewButton>(glm::vec2(270, 262), "mode");
  m_Root.AddChild(RefreshButton);
  m_Root.AddChild(ModeButton);
  stash.push_back(RefreshButton);
  stash.push_back(ModeButton);
  IsModePress = false;

  m_CurrentState = State::UPDATE;
};

void FourthLevel::ResetObject() {
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
  ModeButton.reset();
  RefreshButton.reset();
};

void FourthLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  ModeButton->Update();
  LOG_DEBUG(IsModePress);
  if (ModeButton->GetIsPressed()) {

    IsModePress = !IsModePress;
  }
  if (!doors[1]->GetIsOpen() || !doors[0]->GetIsOpen()) {
    bool firedoor = (doors[0]->IsCharacterInto(fireboy, watergirl));
    bool waterdoor = (doors[1]->IsCharacterInto(fireboy, watergirl));
    if (firedoor && waterdoor) {
      doors[0]->OpenDoor();
      doors[1]->OpenDoor();
    }
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
    if (!IsModePress) {
      fireboy->SetPool(Pools);
      watergirl->SetPool(Pools);
    } else {
      fireboy->SetPool({});
      watergirl->SetPool({});
    }
    fireboy->SetElevators(elevators);
    watergirl->SetElevators(elevators);
    fireboy->SetDoor(doors);
    watergirl->SetDoor(doors);

    for (auto pool : Pools) {
      if (!pool->IsLooping()) {
        pool->SetLooping(true);
      }
    }

    watergirl->Update(deltaTime, mapbackground->GetLevelData(3).platforms);
    fireboy->Update(deltaTime, mapbackground->GetLevelData(3).platforms);

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
  }
  TriggerStage(counter_fire, counter_water, Enum::PhaseEnum::IntroductionPage,
               stash, [this]() { ResetObject(); });
  m_Root.Update();
};
void FourthLevel::End() {
  if (music)
    music->FadeOut(50);
  phase = Enum::PhaseEnum::FourthLevel;
  RetryAnything();
  for (auto item : stash) {
    m_Root.RemoveChild(item);
  }
  music.reset();
  m_CurrentState = App::State::START;
};