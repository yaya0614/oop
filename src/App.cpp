#include "App.hpp"

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

  // 清空 stash，釋放記憶體
  stash.clear();
};

void App::TriggerStage(int counter_fire, int counter_water) {
  if (fireboy->GetStatus() == "Die" || watergirl->GetStatus() == "Die") {
    m_Root.AddChild(stages_over);
    stages_over->Update(0, 0);

    if (stages_over->GetRetryButton()->GetIsPressed()) {
      RetryAnything();
      Start(); // 確保重新初始化物件
    }

    if (stages_over->GetMainButton()->GetIsPressed()) {
      // 確保清除畫面，然後回到首頁
      RetryAnything();
      NavigationTo(Enum::PhaseEnum::IntroductionPage);
    }
  } else if ((fireboy->GetStatus() == "InDoor" &&
              watergirl->GetStatus() == "InDoor")) {
    m_Root.AddChild(stages);
    stages->Update(counter_water, counter_fire);

    if (stages->GetRetryButton()->GetIsPressed()) {
      RetryAnything();
      Start();
    }

    if (stages->GetMainButton()->GetIsPressed()) {
      RetryAnything();
      NavigationTo(Enum::PhaseEnum::IntroductionPage);
    }
  }
};
