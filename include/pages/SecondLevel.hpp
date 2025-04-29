#ifndef SECONDLEVEL_HPP
#define SECONDLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "Stage.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewRock.hpp"
#include "actors/NewWaterGirl.hpp"
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
  std::shared_ptr<NewWaterGirl> Girl;
  std::shared_ptr<NewRock> Rock;
  std::shared_ptr<NewPool> Pool;

  std::shared_ptr<NewElevator> elevator;
  std::vector<std::shared_ptr<NewPool>> Pools;
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewSwitch>> switches;

  std::shared_ptr<Stage> m_stage;
  std::shared_ptr<MapBackground> mapbackground;
};

#endif // SECONDLEVEL_HPP