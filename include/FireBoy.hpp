#ifndef FIREBOY_HPP
#define FIREBOY_HPP

#include <string>

#include "PhaseResourceManger.hpp"

#include "Util/GameObject.hpp"

class FireBoy : public Util::GameObject {
public:
  explicit FireBoy(const std::string &ImagePath);

  FireBoy(const FireBoy &) = delete;

  FireBoy(FireBoy &&) = delete;

  FireBoy &operator=(const FireBoy &) = delete;

  FireBoy &operator=(FireBoy &&) = delete;

  [[nodiscard]] const std::string &GetImagePath() const { return m_ImagePath; }

  [[nodiscard]] const glm::vec2 &GetPosition() const {
    return m_Transform.translation;
  }

  [[nodiscard]] bool GetVisibility() const { return m_Visible; }

  void SetImage(const std::string &ImagePath);

  void SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
  }
  bool
  IsOverlines(float expect_x, float expect_y,
              const std::shared_ptr<PhaseResourceManger> &background) const {
    float min_x = background->GetMinX();
    float max_x = background->GetMaxX();
    float min_y = background->GetMinY();
    float max_y = background->GetMaxY();

    // 計算角色的新邊界
    float character_min_x = expect_x - GetScaledSize().x / 2;
    float character_max_x = expect_x + GetScaledSize().x / 2;
    float character_min_y = expect_y - GetScaledSize().y / 2;
    float character_max_y = expect_y + GetScaledSize().y / 2;

    // 如果超過背景範圍，回傳 true（代表不能移動）
    if (character_max_x > max_x || character_min_x < min_x ||
        character_max_y > max_y || character_min_y < min_y) {
      return true;
    }
    return false;
  }
  // TODO: Implement the collision detection
  [[nodiscard]] bool IfCollides(const std::shared_ptr<FireBoy> &other) const {
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
  IfCollides_door(const std::shared_ptr<FireBoy> &other) const {
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
