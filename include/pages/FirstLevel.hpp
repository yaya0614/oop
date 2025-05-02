#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "Stage.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewWaterGirl.hpp"
#include "machines/NewSwitch.hpp"

class FirstLevel : public App {
public:
  explicit FirstLevel() { phase = Enum::PhaseEnum::FirstLevel; }
  std::shared_ptr<Character> Background;
  std::shared_ptr<NewFireBoy> fireboy;
  std::shared_ptr<NewWaterGirl> Girl;
  std::shared_ptr<NewRock> Rock;
  std::shared_ptr<NewPool> Pool;
  std::shared_ptr<Stage> stages;

  std::shared_ptr<NewElevator> elevator;
  std::vector<std::shared_ptr<NewPool>> Pools;
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewSwitch>> switches;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<Diamond>> diamonds;

  std::shared_ptr<Stage> m_stage;
  std::shared_ptr<MapBackground> mapbackground;
  void Start() override;
  void Update() override;
  void End() override;
};

#endif // FIRSTLEVEL_HPP