#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Button.hpp"
#include "Character.hpp"
#include "Elevation.hpp"
#include "ElevationPurple.hpp"
#include "FireBoy.hpp"
#include "FireDoor.hpp"
#include "Pusher.hpp"
#include "Rock.hpp"
#include "WaterDoor.hpp"
#include "WaterGirl.hpp"

#include "FireSea.hpp"
#include "MapBackground.hpp"
#include "Util/Logger.hpp"
#include <memory>
#include <string>
#include <vector>

void App::Start() {

  LOG_DEBUG("Start");

  // start_btn = std::make_shared<Character>(GA_RESOURCE_DIR
  //                                         "/Image/Background/start_btn.png");
  // start_btn->SetPosition({0, -180});
  // start_btn->SetZIndex(50);
  // m_Root.AddChild(start_btn);

  fire_boy = std::make_shared<FireBoy>();
  fire_boy->m_Transform.scale = {0.4, 0.41f};
  m_Root.AddChild(fire_boy);

  water_girl = std::make_shared<WaterGirl>();
  water_girl->m_Transform.scale = {0.4, 0.41f};
  m_Root.AddChild(water_girl);

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

  m_fireSea = std::make_shared<FireSea>();
  m_Root.AddChild(m_fireSea);

  ele_blue = std::make_shared<Elevation>();
  m_Root.AddChild(ele_blue);

  rock = std::make_shared<Rock>();
  m_Root.AddChild(rock);

  ele_purple = std::make_shared<ElevationPurple>();
  m_Root.AddChild(ele_purple);

  button = std::make_shared<Button>();
  m_Root.AddChild(button);

  pusher = std::make_shared<Pusher>();
  m_Root.AddChild(pusher);

  firedoor = std::make_shared<FireDoor>();
  m_Root.AddChild(firedoor);

  waterdoor = std::make_shared<WaterDoor>();
  m_Root.AddChild(waterdoor);

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);

  m_CurrentState = State::UPDATE;
}
