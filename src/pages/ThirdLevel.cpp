#include "pages/ThirdLevel.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

void ThirdLevel::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel2.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);

  fireboy = std::make_shared<NewFireBoy>(glm::vec2(240, -100));
  m_Root.AddChild(fireboy);
  // y = -240
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(300, 200));
  m_Root.AddChild(watergirl);
  stages = std::make_shared<Stage>();

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

  // doors
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-310, 221),
                                            glm::vec2(0, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(-240, 221),
                                            glm::vec2(0, 30), "water"));
  for (auto &s : switches) {
    m_Root.AddChild(s);
  }
  for (auto &ele : elevators) {
    m_Root.AddChild(ele);
  }

  for (auto &pool : Pools) {
    m_Root.AddChild(pool);
  }
  for (auto &door : doors) {
    m_Root.AddChild(door);
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
  }

  for (auto &pos : waterDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "water");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);
  m_CurrentState = State::UPDATE;
};

void ThirdLevel::Update() {

  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  for (auto &pool : Pools) {
    if (!pool->IsLooping()) {
      pool->SetLooping(true);
    }
  }
  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  fireboy->SetElevators(elevators);
  watergirl->SetElevators(elevators);
  fireboy->SetDoor(doors);
  watergirl->SetDoor(doors);
  fireboy->SetPool(Pools);
  watergirl->SetPool(Pools);

  for (auto door : doors) {
    if (!door->GetIsOpen()) {
      door->IsCharacterInto(fireboy, watergirl);
    }
  }

  fireboy->Update(deltaTime, mapbackground->GetLevelData(2).platforms);
  watergirl->Update(deltaTime, mapbackground->GetLevelData(2).platforms);

  for (auto s : switches) {
    s->UpdateSwitchState(fireboy, watergirl, deltaTime, elevators);
  }
  for (auto ele : elevators) {
    std::string eleColor = ele->GetColor();

    bool anyButtonPressed = false;
    bool allButtonReleased = true;
    int lever_dir = 0;

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
      diamond->Update();
    }
    if (diamond->IsCollected())
      continue;

    if (diamond->tag == "fire" && fireboy->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }

    if (diamond->tag == "water" && watergirl->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }
  }

  if ((fireboy->GetStatus() == "InDoor" &&
       watergirl->GetStatus() == "InDoor") ||
      (fireboy->GetStatus() == "Die" || watergirl->GetStatus() == "Die")) {
    m_Root.AddChild(stages);

    // stages->Update(diamonds[0]->GetDiamondAmonut(),
    //                diamonds[1]->GetDiamondAmonut());
    // if (stages->GetRetryButton()->GetIsPressed()) {
    //   NavigationTo(Enum::PhaseEnum::FirstLevel);
    // }
    // if (stages->GetMainButton()->GetIsPressed()) {
    //   NavigationTo(Enum::PhaseEnum::FirstLevel);
    // }
  }
  m_Root.Update();
};

void ThirdLevel::End(){
    // Implementation here
};