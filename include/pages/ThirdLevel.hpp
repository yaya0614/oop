#ifndef THIRDLEVEL_HPP
#define THIRDLEVEL_HPP

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

class ThirdLevel : public App {
public:
  explicit ThirdLevel() { phase = Enum::PhaseEnum::ThirdLevel; }

  std::shared_ptr<Character> Background;
  std::shared_ptr<NewFireBoy> fireboy;
  std::shared_ptr<NewWaterGirl> watergirl;
  std::vector<std::shared_ptr<NewPool>> Pools;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<Diamond>> diamonds;

  std::shared_ptr<Stage> stages;
  std::shared_ptr<MapBackground> mapbackground;

  float deltaTime = 1.0 / 60.0f;

  void Start() override;
  void Update() override;
  void End() override;
};

#endif