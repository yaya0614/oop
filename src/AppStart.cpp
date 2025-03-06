#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Character.hpp"
#include "FireBoy.hpp"
#include "MapBackground.hpp"
#include "Util/Logger.hpp"
#include <memory>

void App::Start() {

  LOG_DEBUG("Start");

  start_btn = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Background/start_btn.png");
  start_btn->SetPosition({0, -180});
  start_btn->SetZIndex(50);
  // m_Root.AddChild(start_btn);

  fire_boy = std::make_shared<FireBoy>();
  // fire_boy->Set({0, 0});
  fire_boy->SetZIndex(55);
  fire_boy->m_Transform.scale = {0.4, 0.4f};
  m_Root.AddChild(fire_boy);

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);

  // LOG_DEBUG(Fire_boy->GetScaledSize());
  // m_PRM = std::make_shared<PhaseResourceManger>();
  // m_Root.AddChildren(m_PRM->GetChildren());

  m_CurrentState = State::UPDATE;
}
