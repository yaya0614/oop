#ifndef BACKROUNDTEMPLATE_HPP
#define BACKROUNDTEMPLATE_HPP

#include "BackgroundImage.hpp"
#include "Character.hpp"
#include "TaskText.hpp"
#include "Util/GameObject.hpp"

class BackgroundTemplate : public Character {
public:
  BackgroundTemplate();

  [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
  GetChildren() const {
    return {m_TaskText, m_Background};
  }

  void NextPhase();
  void IsPressed();

private:
  std::shared_ptr<TaskText> m_TaskText;
  std::shared_ptr<BackgroundImage> m_Background;

  int m_Phase = 1;
};

#endif // PHASE_MANGER_HPP
