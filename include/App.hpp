#ifndef APP_HPP
#define APP_HPP

#include "Button.hpp"
#include "Elevation.hpp"
#include "ElevationPurple.hpp"
#include "FireBoy.hpp"
#include "FireSea.hpp"
#include "MapBackground.hpp"
#include "Pusher.hpp"
#include "WaterGirl.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "AnimatedCharacter.hpp"
#include "Character.hpp"
#include "PhaseResourceManger.hpp"
#include "Util/Renderer.hpp"
#include "Util/Text.hpp"
#include <memory>

class App {
public:
  enum class State {
    START,
    UPDATE,
    END,
  };

  State GetCurrentState() const { return m_CurrentState; }

  void Start();

  void Update();

  void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
  void ValidTask();

private:
  enum class Phase {
    CHANGE_CHARACTER_IMAGE,
    ABLE_TO_MOVE,
    COLLIDE_DETECTION,
    BEE_ANIMATION,
    OPEN_THE_DOORS,
    COUNTDOWN,
  };

  State m_CurrentState = State::START;
  Phase m_Phase = Phase::CHANGE_CHARACTER_IMAGE;

  Util::Renderer m_Root;

  std::shared_ptr<Character> start_btn;
  std::shared_ptr<FireBoy> fire_boy;
  std::shared_ptr<WaterGirl> water_girl;
  std::shared_ptr<Character> m_Chest;
  std::shared_ptr<MapBackground> mapbackground;

  std::vector<std::shared_ptr<Character>> m_Doors;
  std::shared_ptr<Elevation> ele_blue;
  std::shared_ptr<ElevationPurple> ele_purple;
  std::shared_ptr<Button> button;
  std::shared_ptr<Pusher> pusher;
  std::shared_ptr<AnimatedCharacter> m_Bee;
  std::shared_ptr<AnimatedCharacter> m_Ball;

  std::shared_ptr<AnimatedCharacter> ice_sea;

  std::shared_ptr<FireSea> m_fireSea;
  std::shared_ptr<PhaseResourceManger> m_PRM;

  bool m_EnterDown = false;
};

#endif
