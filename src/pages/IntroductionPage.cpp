#include "pages/IntroductionPage.hpp"
#include "Character.hpp"
#include "Enum.hpp"
#include "NewButton.hpp"
#include "Stage.hpp"
#include "Util/BGM.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "enum.hpp"
#include <memory>

void IntroductionPage::Start() {
  LOG_INFO("START INTR");
  music = std::make_shared<Util::BGM>(GA_RESOURCE_DIR
                                      "/Fireboy and Watergirl Main Menu.mp3");
  Background = std::make_shared<Character>(
      GA_RESOURCE_DIR "/Image/Background/IntroductionPage.png");
  Background->SetVisible(true);
  Background->SetZIndex(50);
  Background->m_Transform.scale = {0.81, 0.9};
  m_Root.AddChild(Background);

  button = std::make_shared<NewButton>(glm::vec2(0, -180), "play");
  m_Root.AddChild(button);
  music->Play(-1);
  music->SetVolume(50);
  m_CurrentState = State::UPDATE;
};

void IntroductionPage::Update() {

  button->Update();
  LOG_DEBUG(button->GetIsPressed());
  if (button->GetIsPressed()) {

    NavigationTo(Enum::PhaseEnum::FirstLevel);
  }
  m_Root.Update();
};

void IntroductionPage::End() {
  LOG_INFO("START END");
  if (music)
    music->FadeOut(50);

  phase = Enum::PhaseEnum::IntroductionPage;

  m_Root.RemoveChild(button);
  m_Root.RemoveChild(Background);
  music.reset();

  m_CurrentState = State::START;
};