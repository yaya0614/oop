#include "App.hpp"

#include "Core/Context.hpp"
#include "Util/Logger.hpp"
#include "enum.hpp"
#include "pages/FirstLevel.hpp"
#include "pages/FourthLevel.hpp"
#include "pages/IntroductionPage.hpp"
#include "pages/SecondLevel.hpp"
#include "pages/ThirdLevel.hpp"

#include <memory>
#include <vector>

int main(int, char **) {

  auto context = Core::Context::GetInstance();
  auto phases = std::vector<std::shared_ptr<App>>();

  auto currentPhase = Enum::PhaseEnum::FirstLevel;
  phases.push_back(std::make_shared<IntroductionPage>(IntroductionPage()));
  phases.push_back(std::make_shared<FirstLevel>(FirstLevel()));
  phases.push_back(std::make_shared<SecondLevel>(SecondLevel()));
  phases.push_back(std::make_shared<ThirdLevel>(ThirdLevel()));
  phases.push_back(std::make_shared<FourthLevel>(FourthLevel()));

  while (!context->GetExit()) {
    auto &phase = phases[static_cast<size_t>(currentPhase)];

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {

      context->SetExit(true);
      continue;
    }
    if (phase && (phase->GetPhase() != currentPhase)) {
      currentPhase = phase->GetPhase();
    }
    switch (phase->GetCurrentState()) {
    case App::State::START:
      phase->Start();
      break;

    case App::State::UPDATE:
      phase->Update();
      break;

    case App::State::END:
      phase->End();
      break;
    }
    context->Update();
  }
  return 0;
}
