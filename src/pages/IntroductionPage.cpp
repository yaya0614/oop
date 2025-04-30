#include "pages/IntroductionPage.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "NewButton.hpp"
#include "Util/Input.hpp"
#include <memory>

void IntroductionPage::Start() {
  Background = std::make_shared<Character>(GA_RESOURCE_DIR
                                           "/Image/Background/background.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  m_Root.AddChild(Background);

  // button = std::make_shared<NewButton>(glm::vec2(0, 0), "main");

  // m_Root.AddChild(button);
  start_btn = std::make_shared<Character>(GA_RESOURCE_DIR
                                          "/Image/Background/start_btn.png");
  start_btn->SetPosition({0, -180});
  start_btn->SetZIndex(55);
  m_Root.AddChild(start_btn);
  m_CurrentState = State::UPDATE;
};

void IntroductionPage::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    if (start_btn) {
      int x = start_btn->GetPosition().x;
      int y = start_btn->GetPosition().y;
      if (mousePos.x - x < 30 && mousePos.y - y < 30) {
        start_btn.reset();
        NavigationTo(Enum::PhaseEnum::FirstLevel);
      }
    }
  }

  button->Update();
  m_Root.Update();
};

void IntroductionPage::End(){
    // Implementation here
};