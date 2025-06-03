#include "pages/SecondLevel.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "enum.hpp"
#include <glm/fwd.hpp>
void SecondLevel::Start() {
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Theme.mp3");

  music->SetVolume(64);
  music->Play(-1);
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel2.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  stages = std::make_shared<Stage>("stage");
  stages_over = std::make_shared<Stage>("stage_over");

  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-320, -244));
  m_Root.AddChild(fireboy);
  // y = -240
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(-260, -244));
  m_Root.AddChild(watergirl);
  BasicAddStash();
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-160, -216), glm::vec2(55, -7), "fire", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(70, -216), glm::vec2(55, -7), "water", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-160, -277), glm::vec2(55, -7), "water", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(70, -277), glm::vec2(55, -7), "fire", glm::vec2(1, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(-152, -17), glm::vec2(60, -7), "green", glm::vec2(0.6, 0.36)));
  Pools.push_back(std::make_shared<NewPool>(
      glm::vec2(182, -17), glm::vec2(60, -7), "green", glm::vec2(0.62, 0.36)));

  elevators.push_back(
      std::make_shared<NewElevator>(glm::vec2(120, 163), glm::vec2(30, 2),
                                    "yellow", 15, glm::vec2(0.55, 0.36), "x"));

  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(170, 197), glm::vec2(20, 5), "yellow",
      true)); // button(每個switch都要調y的觸發點，才可以準確觸發碰撞項)
  switches.push_back(std::make_shared<NewSwitch>(
      glm::vec2(-100, 197), glm::vec2(20, 5), "yellow", true)); // button

  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-310, 221),
                                            glm::vec2(5, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-240, 221),
                                            glm::vec2(5, 30), "water"));
  for (auto &s : switches) {
    m_Root.AddChild(s);
    stash.push_back(s);
  }
  for (auto &ele : elevators) {
    m_Root.AddChild(ele);
    stash.push_back(ele);
  }

  for (auto &pool : Pools) {
    m_Root.AddChild(pool);
    stash.push_back(pool);
  }
  for (auto &door : doors) {
    m_Root.AddChild(door);
    stash.push_back(door);
  }

  std::vector<glm::vec2> redDiamondPositions = {
      {-190, -175}, {-128, -175}, {35, -240}, {105, -240},
      {192, -88},   {-110, -54},  {-15, 30},  {-15, 186},

  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {-190, -240}, {-128, -240}, {35, -175}, {105, -175},
      {107, -58},   {-210, -87},  {33, 30},   {33, 186},

  };
  for (auto &pos : redDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "fire");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
    stash.push_back(diamond);
  }

  for (auto &pos : waterDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "water");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
    stash.push_back(diamond);
  }

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);
  m_Root.Update();
  RefreshButton = std::make_shared<NewButton>(glm::vec2(350, 250), "Refresh");
  m_Root.AddChild(RefreshButton);
  stash.push_back(RefreshButton);
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
};
void SecondLevel::Update() {

  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
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
    fireboy->SetElevators(elevators);
    watergirl->SetElevators(elevators);
    fireboy->SetDoor(doors);
    watergirl->SetDoor(doors);
    fireboy->SetPool(Pools);
    watergirl->SetPool(Pools);
    for (auto &pool : Pools) {
      if (!pool->IsLooping()) {
        pool->SetLooping(true);
      }
    }
    for (auto door : doors) {
      if (!door->GetIsOpen()) {
        door->IsCharacterInto(fireboy, watergirl);
      }
    }

    fireboy->Update(deltaTime, mapbackground->GetLevelData(1).platforms);
    watergirl->Update(deltaTime, mapbackground->GetLevelData(1).platforms);

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
    TriggerStage(counter_fire, counter_water, Enum::PhaseEnum::ThirdLevel,
                 stash, [this]() { ResetObject(); });

    m_Root.Update();
  }
};

void SecondLevel::End() {

  if (music)
    music->FadeOut(50);
  phase = Enum::PhaseEnum::SecondLevel;
  RetryAnything();
  ResetObject();
  m_CurrentState = App::State::START;
};
