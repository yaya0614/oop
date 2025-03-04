#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
  explicit Character(const std::string &ImagePath);

  Character(const Character &) = delete;

  Character(Character &&) = delete;

  Character &operator=(const Character &) = delete;

  Character &operator=(Character &&) = delete;

  [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  [[nodiscard]] bool GetVisibility() const { return m_Visible; }

  void SetImage(const std::string &ImagePath);

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }

  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<Character> &other) const {
    (void)other;
    float x_self = GetPosition().x;
    float y_self = GetPosition().y;
    float x_other = other->GetPosition().x;
    float y_other = other->GetPosition().y;

    if (((-20 < x_self - x_other) && (x_self - x_other < 20)) &&
        ((-20 < y_self - y_other) && (y_self - y_other < 20))) {
      other->SetVisible(false);
      return true;
    }

    return false;
  }

  [[nodiscard]] void
  IfCollides_door(const std::shared_ptr<Character> &other) const {
    (void)other;
    float x_self = GetPosition().x;
    float y_self = GetPosition().y;
    float x_other = other->GetPosition().x;
    float y_other = other->GetPosition().y;

    if (((-20 < x_self - x_other) && (x_self - x_other < 20)) &&
        ((-20 < y_self - y_other) && (y_self - y_other < 20))) {
      other->SetImage(GA_RESOURCE_DIR "/Image/Character/door_open.png");
    }
  }

  // TODO: Add and implement more methods and properties as needed to finish
  // Giraffe Adventure.

private:
  void ResetPosition() { m_Transform.translation = {0, 0}; }

  std::string m_ImagePath;
};

#endif // CHARACTER_HPP
