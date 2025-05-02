#ifndef SECONDLEVEL_HPP
#define SECONDLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "Stage.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewRock.hpp"
#include "actors/NewWaterGirl.hpp"
#include "machines/NewDoor.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"
#include "machines/NewSwitch.hpp"
#include <memory>
#include <vector>

class SecondLevel : public App {
public:
  explicit SecondLevel() { phase = Enum::PhaseEnum::SecondLevel; }

  void Start() override;
  void Update() override;
  void End() override;

  std::shared_ptr<Character> Background;
  std::shared_ptr<NewFireBoy> fireboy;
  std::shared_ptr<NewWaterGirl> watergirl;
  std::vector<std::shared_ptr<NewPool>> Pools;
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewSwitch>> switches;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<Diamond>> diamonds;
  std::shared_ptr<Stage> stages;

  std::shared_ptr<MapBackground> mapbackground;

  float deltaTime = 1.0 / 60.0f;
};

#endif // SECONDLEVEL_HPP