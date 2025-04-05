#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"
#include "enum.hpp"
#include "pch.hpp" // IWYU pragma: export
#include <memory>

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

  void NavigationTo(Enum::PhaseEnum phase) { this->phase = phase; }

  Enum::PhaseEnum phase;
  Util::Renderer m_Root;
  State m_CurrentState = State::START;
};

#endif
