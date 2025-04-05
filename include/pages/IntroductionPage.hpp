#ifndef INTRODUCTIONPAGE_HPP
#define INTRODUCTIONPAGE_HPP

#include "../App.hpp"
#include "Character.hpp"
#include <memory>

class IntroductionPage : public App {
public:
  explicit IntroductionPage() { phase = Enum::PhaseEnum::IntroductionPage; }
  std::shared_ptr<Character> Background;
  std::shared_ptr<Character> start_btn;

  void Start() override;
  void Update() override;
  void End() override;
};

#endif // INTRODUCTIONPAGE_HPP