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
  void ResetObject() override;

private:
  std::vector<glm::vec2> redDiamondPositions = {
      {-190, -175}, {-128, -175}, {35, -240}, {105, -240},
      {192, -88},   {-110, -54},  {-15, 30},  {-15, 186},
  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {-190, -240}, {-128, -240}, {35, -175}, {105, -175},
      {107, -58},   {-210, -87},  {33, 30},   {33, 186},
  };
};

#endif // SECONDLEVEL_HPP