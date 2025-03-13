#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Button.hpp"
#include "Character.hpp"
#include "Elevation.hpp"
#include "FireBoy.hpp"
#include "MapBackground.hpp"
#include "Util/Logger.hpp"
#include <memory>
#include <string>
#include <vector>

void App::Start() {

  LOG_DEBUG("Start");

  start_btn = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Background/start_btn.png");
  start_btn->SetPosition({0, -180});
  start_btn->SetZIndex(50);
  // m_Root.AddChild(start_btn);

  fire_boy = std::make_shared<FireBoy>();
  fire_boy->m_Transform.scale = {0.4, 0.41f};
  m_Root.AddChild(fire_boy);

  fire_sea = std::make_shared<AnimatedCharacter>(std::vector<std::string>{
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_1.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_2.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_3.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_4.png",
      GA_RESOURCE_DIR "/FireBoy/fire_small/fire_5.png",
  });
  fire_sea->SetPosition({170, -310});
  fire_sea->SetZIndex(100);
  fire_sea->m_Transform.scale = {0.7, 0.43};
  fire_sea->SetVisible(true);
  m_Root.AddChild(fire_sea);

  ice_sea = std::make_shared<AnimatedCharacter>(std::vector<std::string>{
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_1.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_2.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_3.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_4.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_5.png",
  });
  ice_sea->SetPosition({20, -310});
  ice_sea->SetZIndex(100);
  ice_sea->m_Transform.scale = {0.7, 0.43};
  ice_sea->SetVisible(true);
  m_Root.AddChild(ice_sea);

  ele_blue = std::make_shared<Elevation>();
  m_Root.AddChild(ele_blue);
  button = std::make_shared<Button>();
  m_Root.AddChild(button);

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);

  // LOG_DEBUG(Fire_boy->GetScaledSize());
  // m_PRM = std::make_shared<PhaseResourceManger>();
  // m_Root.AddChildren(m_PRM->GetChildren());

  m_CurrentState = State::UPDATE;
}
