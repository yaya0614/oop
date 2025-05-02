#include "pages/ThirdLevel.hpp"
#include "MapBackground.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>

void ThirdLevel::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel3.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  mapbackground = std::make_shared<MapBackground>();
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(-342, -254));
  m_Root.AddChild(fireboy);
  // y = -240
  watergirl = std::make_shared<NewWaterGirl>(glm::vec2(342, -254));
  m_Root.AddChild(watergirl);

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
                                            glm::vec2(0, 30), "fire"));
  doors.push_back(std::make_shared<NewDoor>(glm::vec2(125, -51),
                                            glm::vec2(0, 30), "water"));

  std::vector<glm::vec2> redDiamondPositions = {
      {-190, -258}, {-130, -258}, {232, -161}, {275, -130}, {197, -41},
      {366, 3},     {213, 51},    {358, 155},  {134, 215},  {140, 126}};

  std::vector<glm::vec2> waterDiamondPositions = {
      {138, -258}, {198, -258}, {-232, -161}, {-275, -130}, {-339, 1},
      {-227, 97},  {-353, 132}, {-191, 211},  {-131, 112}

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

  for (auto pool : Pools) {
    m_Root.AddChild(pool);
  }
  for (auto door : doors) {
    m_Root.AddChild(door);
  }
  m_Root.AddChild(Background);
  stages = std::make_shared<Stage>();
  m_CurrentState = State::UPDATE;
};

void ThirdLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  for (auto &pool : Pools) {
    if (!pool->IsLooping()) {
      pool->SetLooping(true);
    }
  }
  fireboy->SetDoor(doors);
  fireboy->SetPool(Pools);
  watergirl->SetDoor(doors);
  watergirl->SetPool(Pools);

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