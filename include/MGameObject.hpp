#ifndef MGAMEOBJECT_HPP
#define MGAMEOBJECT_HPP

#include <Util/GameObject.hpp>
class MGameObject : public Util::GameObject {
public:
  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }
};
#endif