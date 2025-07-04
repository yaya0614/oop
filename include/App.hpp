#ifndef APP_HPP
#define APP_HPP

#include "Character.hpp"
#include "Diamond.hpp"
#include "Stage.hpp"
#include "Util/BGM.hpp"
#include "Util/Renderer.hpp"
#include "actors/NewFireBoy.hpp"
#include "actors/NewWaterGirl.hpp"
#include "enum.hpp"
#include "machines/NewBridge.hpp"
#include "machines/NewSwitch.hpp"
#include "pch.hpp" // IWYU pragma: export
#include <functional>
#include <memory>
#include <string>
#include <vector>

class App {
public:
  enum class State {
    START,
    UPDATE,
    END,
  };

  State GetCurrentState() const { return m_CurrentState; }
  Enum::PhaseEnum GetPhase() const { return phase; }

  virtual ~App() = default;

  virtual void Start();

  virtual void Update();

  virtual void End();
  void RetryAnything();
  virtual void ResetObject();

  void
  TriggerStage(int counter_fire, int counter_water, Enum::PhaseEnum m_phase,
               std::vector<std::shared_ptr<Util::GameObject>> stash_from_self,
               std::function<void()> func);
  void TriggerBtnOrLever();
  void NavigationTo(Enum::PhaseEnum phase) {
    this->phase = phase;
    m_CurrentState = State::END;
  }
  void BasicAddStash();
  Enum::PhaseEnum phase;
  Util::Renderer m_Root;
  State m_CurrentState = State::START;

protected:
  std::shared_ptr<NewButton> button;
  std::shared_ptr<NewButton> RefreshButton;
  std::shared_ptr<NewButton> ModeButton;

  std::shared_ptr<Character> Background;
  std::shared_ptr<NewFireBoy> fireboy;
  std::shared_ptr<NewWaterGirl> watergirl;

  std::shared_ptr<NewRock> Rock;
  std::shared_ptr<NewPool> Pool;
  std::shared_ptr<Stage> stages;
  std::shared_ptr<Stage> stages_over;
  std::vector<std::shared_ptr<NewBridge>> bridges;
  std::vector<std::shared_ptr<NewBridge>> bridge_line;

  std::shared_ptr<NewElevator> elevator;
  std::vector<std::shared_ptr<NewPool>> Pools;
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewSwitch>> switches;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<Diamond>> diamonds;

  std::shared_ptr<Stage> m_stage;
  std::shared_ptr<MapBackground> mapbackground;

  std::vector<std::shared_ptr<Util::GameObject>> stash;
  std::shared_ptr<Util::BGM> music;

  float deltaTime = 1.0 / 60.0f;
  bool IsModePress = false;
  int counter_fire = 0;
  int counter_water = 0;
};

#endif
