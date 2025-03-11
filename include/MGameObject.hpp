#ifndef MGAMEOBJECT_HPP
#define MGAMEOBJECT_HPP

#include <Util/GameObject.hpp>
#include <glm/fwd.hpp>
class MGameObject : public Util::GameObject {
public:
  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  const glm::vec2 &GetPosition() const { return m_Transform.translation; }

  const float GetHeight() { return GetScaledSize().y + GetScaledSize().y / 2; };
  const float GetWidth() { return GetScaledSize().x + GetScaledSize().x / 2; };
  // glm::vec2 GetChracterSize(){return {m_Transform.translation.x+}};
  const float GetHalfHeight() { return GetScaledSize().y / 2; };
  const float GetHalfWidth() { return GetScaledSize().x / 2; };
};
#endif