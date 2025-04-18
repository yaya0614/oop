#ifndef SECONDLEVEL_HPP
#define SECONDLEVEL_HPP

#include "../App.hpp"
#include "Character.hpp"
#include "actors/NewFireBoy.hpp"

class SecondLevel : public App {
public:
  explicit SecondLevel() { phase = Enum::PhaseEnum::SecondLevel; }

  void Start() override;
  void Update() override;
  void End() override;

  std::shared_ptr<Character> Background;
  std::shared_ptr<NewFireBoy> fireboy;
  std::shared_ptr<MapBackground> mapbackground;
};

#endif // SECONDLEVEL_HPP