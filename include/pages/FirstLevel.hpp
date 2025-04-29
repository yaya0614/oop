#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include "../App.hpp"
#include "AnimatedCharacter.hpp"
#include "Button.hpp"
#include "ButtonTop.hpp"
#include "Character.hpp"
#include "Diamond.hpp"
#include "FireBoy.hpp"

#include "FireDoor.hpp"
#include "FireSea.hpp"
#include "Pusher.hpp"
#include "WaterDoor.hpp"
#include "WaterGirl.hpp"

class FirstLevel : public App {
public:
  explicit FirstLevel() { phase = Enum::PhaseEnum::FirstLevel; }

  void Start() override;
  void Update() override;
  void End() override;

  std::shared_ptr<FireBoy> fire_boy;
  std::shared_ptr<WaterGirl> water_girl;
  std::shared_ptr<Character> m_Chest;
  std::shared_ptr<MapBackground> mapbackground;
  std::shared_ptr<Character> Background;

  std::vector<std::shared_ptr<Character>> m_Doors;
  std::shared_ptr<Elevation> ele_blue;
  std::shared_ptr<ElevationPurple> ele_purple;

  std::shared_ptr<Button> button;
  std::shared_ptr<Pusher> pusher;
  std::shared_ptr<AnimatedCharacter> m_Bee;
  std::shared_ptr<AnimatedCharacter> m_Ball;
  std::shared_ptr<FireDoor> firedoor;
  std::shared_ptr<WaterDoor> waterdoor;

  std::shared_ptr<ButtonTop> button_top;

  std::shared_ptr<AnimatedCharacter> ice_sea;
  std::vector<std::shared_ptr<Diamond>> diamonds;
  std::shared_ptr<FireSea> m_fireSea;
  std::shared_ptr<Rock> rock;
};

#endif // FIRSTLEVEL_HPP