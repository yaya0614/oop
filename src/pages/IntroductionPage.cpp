#include "pages/IntroductionPage.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "NewButton.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <memory>

void IntroductionPage::Start() {
  Background = std::make_shared<Character>(
      GA_RESOURCE_DIR "/Image/Background/IntroductionPage.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  Background->m_Transform.scale = {0.81, 0.9};
  m_Root.AddChild(Background);

  button = std::make_shared<NewButton>(glm::vec2(0, -180), "play");
  m_Root.AddChild(button);

  m_CurrentState = State::UPDATE;
};

// start menu level
void IntroductionPage::Update() {
  button->Update();
  LOG_DEBUG(button->GetIsPressed());
  if (button->GetIsPressed()) {
    NavigationTo(Enum::PhaseEnum::FirstLevel);
  }
  m_Root.Update();
};

void IntroductionPage::End(){
    // Implementation here
};