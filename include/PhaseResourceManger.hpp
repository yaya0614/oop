#ifndef PHASE_MANGER_HPP
#define PHASE_MANGER_HPP

#include "BackgroundImage.hpp"
// #include "Character.hpp"
#include "TaskText.hpp"
#include "Util/GameObject.hpp"
#include <glm/fwd.hpp>

class PhaseResourceManger : public Util::GameObject {
public:
  PhaseResourceManger();

  [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
  GetChildren() const {
    return {m_TaskText, m_Background};
  }

  void NextPhase();
  void IsPressed();

  float GetMinX() const { return m_Background->GetMinX(); }
  float GetMaxX() const { return m_Background->GetMaxX(); }
  float GetMinY() const { return m_Background->GetMinY(); }
  float GetMaxY() const { return m_Background->GetMaxY(); }

private:
  std::shared_ptr<TaskText> m_TaskText;
  std::shared_ptr<BackgroundImage> m_Background;

  int m_Phase = 1;
};

#endif // PHASE_MANGER_HPP
