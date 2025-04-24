#include "pages/SecondLevel.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "Stage.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "actors/NewFireBoy.hpp"
#include <memory>

void SecondLevel::Start() {

  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/NewLevel1.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);
  fireboy = std::make_shared<NewFireBoy>(glm::vec2(0, -254));
  m_Root.AddChild(fireboy);
  mapbackground = std::make_shared<MapBackground>();

  // m_stage = std::make_shared<Stage>();
  // m_Root.AddChild(m_stage);
  // m_Root.AddChild(mapbackground);
  m_CurrentState = State::UPDATE;
};

void SecondLevel::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }
  float deltaTime = 1.0 / 60.0f;

  fireboy->Update(deltaTime, mapbackground->GetLevelData(1).platforms);

  m_Root.Update();
};

void SecondLevel::End(){
    // Implementation here
};