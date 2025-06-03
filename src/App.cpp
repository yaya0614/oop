#include "App.hpp"
#include "Util/Logger.hpp"

void App::BasicAddStash() {
  stash.push_back(fireboy);
  stash.push_back(watergirl);
  stash.push_back(mapbackground);
  stash.push_back(Background);
  stash.push_back(stages);
  stash.push_back(stages_over);
};
void App::Start(){};
void App::Update(){};
void App::End(){};
void App::ResetObject(){};

void App::TriggerBtnOrLever() {

  for (auto ele : elevators) {
    std::string eleColor = ele->GetColor();

    bool anyButtonPressed = false;
    bool allButtonReleased = true;
    int lever_dir = 0;

    for (auto s : switches) {
      if (s->GetColor() == eleColor && s->IsButtonType()) {
        if (s->IsPressed()) {
          s->ButtonPlayAnimation();
          anyButtonPressed = true;
          allButtonReleased = false;
        }
        s->ButtonPlayAnimation();
      }
    }

    for (auto s : switches) {
      if (s->GetColor() == eleColor && !s->IsButtonType()) {
        lever_dir = s->GetLeverDir();
      }
    }
    if (anyButtonPressed) {
      ele->UpdateBtnActivate(true, deltaTime);
    } else if (lever_dir != 0) {
      ele->UpdateActivate(lever_dir, deltaTime);
    } else if (allButtonReleased) {
      ele->UpdateBtnActivate(false, deltaTime);
    }
  }
};

void App::RetryAnything() {
  for (auto object : stash) {
    m_Root.RemoveChild(object);
  }
  stash.clear();
  fireboy.reset();
  watergirl.reset();
  stages.reset();
  stages_over.reset();
  Background.reset();
  mapbackground.reset();
};

void App::TriggerStage(
    int counter_fire, int counter_water, Enum::PhaseEnum m_phase,
    std::vector<std::shared_ptr<Util::GameObject>> stash_from_self,
    std::function<void()> func) {
  if (fireboy->GetStatus() == "Die" || watergirl->GetStatus() == "Die") {
    if (fireboy->GetStatus() == "Die") {
      fireboy->ChangeStatus("Die");

    } else if (watergirl->GetStatus() == "Die") {
      watergirl->ChangeStatus("Die");
    } else {
      fireboy->ChangeStatus("Die");
      watergirl->ChangeStatus("Die");
    }

    m_Root.AddChild(stages_over);
    stages_over->Update(0, 0);

    if (stages_over->GetRetryButton()->GetIsPressed()) {
      RetryAnything();
      for (auto item : stash_from_self) {
        m_Root.RemoveChild(item);
      }
      func();
      Start(); // 確保重新初始化物件
    }

    if (stages_over->GetMainButton()->GetIsPressed()) {
      NavigationTo(Enum::PhaseEnum::IntroductionPage);
    }
  } else if ((fireboy->GetStatus() == "InDoor" &&
              watergirl->GetStatus() == "InDoor")) {
    m_Root.AddChild(stages);
    stages->Update(counter_water, counter_fire);

    if (stages->GetRetryButton()->GetIsPressed()) {
      RetryAnything();
      for (auto item : stash_from_self) {
        m_Root.RemoveChild(item);
      }
      stash_from_self.clear();
      func();

      Start();
    }

    if (stages->GetMainButton()->GetIsPressed()) {
      NavigationTo(m_phase);
    }
  }
};
