#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include "../App.hpp"

class FirstLevel : public App {
public:
  explicit FirstLevel() { phase = Enum::PhaseEnum::FirstLevel; }

  void Start() override;
  void Update() override;
  void End() override;
  void ResetObject() override;

private:
  std::vector<glm::vec2> redDiamondPositions = {
      {150, -260},
      {-250, 20},
      {-155, 250},
      {0, 200},
  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {20, -260},
      {132, -18},
      {-350, 190},
      {100, 200},
  };
};

#endif // FIRSTLEVEL_HPP