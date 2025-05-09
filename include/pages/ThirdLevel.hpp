#ifndef THIRDLEVEL_HPP
#define THIRDLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "MGameObject.hpp"
#include "Stage.hpp"
#include "Util/GameObject.hpp"
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

  void Start() override;
  void Update() override;
  void End() override;

private:
  std::vector<glm::vec2> redDiamondPositions = {
      {-190, -258}, {-130, -258}, {232, -161}, {275, -130}, {197, -41},
      {366, 3},     {213, 51},    {358, 155},  {134, 215},  {140, 126}};

  std::vector<glm::vec2> waterDiamondPositions = {
      {138, -258}, {198, -258}, {-232, -161}, {-275, -130}, {-339, 1},
      {-227, 97},  {-353, 132}, {-191, 211},  {-131, 112}

  };
};

#endif