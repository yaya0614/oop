#ifndef FOURTHLEVEL_HPP
#define FOURTHLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "Stage.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewWaterGirl.hpp"
#include "machines/NewPool.hpp"
#include "machines/NewSwitch.hpp"
#include <memory>

class FourthLevel : public App {
public:
  explicit FourthLevel() { phase = Enum::PhaseEnum::FourthLevel; }

  void Start() override;
  void Update() override;
  void End() override;

private:
  std::vector<glm::vec2> redDiamondPositions = {
      {-41, -187}, {-42, 58},  {-205, 220},
      {-304, 156}, {-304, 51}, {-342, -115},
  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {19, 177}, {33, -50}, {189, 203}, {307, 129}, {307, 7}

  };
};

#endif // FOURTHLEVEL_HPP