#include "pages/ThirdLevel.hpp"
#include "MapBackground.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "enum.hpp"
#include <glm/fwd.hpp>
#include <memory>

void ThirdLevel::Start() {
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Theme.mp3");

  music->SetVolume(60);
  music->Play(-1);
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel3.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);

  mapbackground = std::make_shared<MapBackground>();
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-342, -240));
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(342, -240)); // y = -240

  stages = std::make_shared<Stage>("stage");
  stages_over = std::make_shared<Stage>("stage_over");

  m_Root.AddChild(fireboy);
  m_Root.AddChild(watergirl);
  m_Root.AddChild(Background);

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-165, -292), glm::vec2(55, -7), "fire", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(165, -292), glm::vec2(55, -7), "water", glm::vec2(1, 0.36)));

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-255, -190), glm::vec2(40, -7), "water", glm::vec2(0.7, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(255, -190), glm::vec2(40, -7), "fire", glm::vec2(0.7, 0.36)));

  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-138, 5), glm::vec2(30, -7), "fire", glm::vec2(0.62, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(119, 5), glm::vec2(30, -7), "water", glm::vec2(0.62, 0.36)));

  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-140, -51),
                                            glm::vec2(5, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(125, -51),
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

  for (auto pool : Pools) {
    m_Root.AddChild(pool);
    stash.push_back(pool);
  }
  for (auto door : doors) {
    m_Root.AddChild(door);
    stash.push_back(door);
  }

  RefreshButton = std::make_shared<NewButton>(glm::vec2(350, 250), "Refresh");
  ModeButton = std::make_shared<NewButton>(glm::vec2(290, 262), "mode");
  m_Root.AddChild(RefreshButton);
  m_Root.AddChild(ModeButton);
  stash.push_back(RefreshButton);
  stash.push_back(ModeButton);
  IsModePress = false;

  m_CurrentState = State::UPDATE;
};

void ThirdLevel::ResetObject() {
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

void ThirdLevel::Update() {
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

    if (!doors[1]->GetIsOpen() || !doors[0]->GetIsOpen()) {
      bool firedoor = (doors[0]->IsCharacterInto(fireboy, watergirl));
      bool waterdoor = (doors[1]->IsCharacterInto(fireboy, watergirl));
      if (firedoor && waterdoor) {
        doors[0]->OpenDoor();
        doors[1]->OpenDoor();
      }
    }

    fireboy->Update(deltaTime, mapbackground->GetLevelData(2).platforms);
    watergirl->Update(deltaTime, mapbackground->GetLevelData(2).platforms);

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
  TriggerStage(counter_fire, counter_water, Enum::PhaseEnum::FourthLevel, stash,
               [this]() { ResetObject(); });
  if (!fireboy || !watergirl) {
    return;
  }
  m_Root.Update();
};

void ThirdLevel::End() {
  if (music)
    music->FadeOut(50);
  phase = Enum::PhaseEnum::ThirdLevel;
  RetryAnything();
  for (auto item : stash) {
    m_Root.RemoveChild(item);
  }
  music.reset();
  m_CurrentState = App::State::START;
};