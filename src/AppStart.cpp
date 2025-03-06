#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Character.hpp"
#include "FireBoy.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {

  LOG_DEBUG("Start");

  start_btn = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Background/start_btn.png");
  start_btn->SetPosition({0, -180});
  start_btn->SetZIndex(50);
  m_Root.AddChild(start_btn);

  // fb = std::make_shared<FireBoy>();
  // m_Root.AddChild(Fire_boy);
  // Fire_boy = std::make_shared<FireBoy>();
  // Fire_boy->SetZIndex(55);
  // Fire_boy->m_Transform.scale = {0.4, 0.4f};
  // m_Root.AddChild(Fire_boy);
  boy = std::make_shared<FireBoy>(GA_RESOURCE_DIR "/FireBoy/boy/boy_1.png");
  boy->SetPosition({0, 0});
  boy->SetZIndex(55);
  boy->m_Transform.scale = {0.4, 0.4f};
  m_Root.AddChild(boy);

  // LOG_DEBUG(Fire_boy->GetScaledSize());
  m_PRM = std::make_shared<PhaseResourceManger>();
  m_Root.AddChildren(m_PRM->GetChildren());

  m_CurrentState = State::UPDATE;
}
