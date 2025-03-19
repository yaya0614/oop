#include "Elevation.hpp"
#include "Util/Image.hpp"
#include <memory>

Elevation::Elevation() {
  SetImage(GA_RESOURCE_DIR "/Elevation/ele_blue.png");
  SetPosition({-358, -28});
  // SetPosition({-358, -108});

  m_Transform.scale = {0.415, 0.4f};
  SetVisible(true);
  SetZIndex(100);
};

void Elevation::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void Elevation::Update(float deltaTime, bool IsPressed) {
  float targetY = IsPressed ? m_TargetY : m_OriginalY;
  float currentY = GetPosition().y;

  if (currentY != targetY) {
    float direction = (targetY > currentY) ? 1.0f : -1.0f;
    float newY = currentY + direction * m_Speed * deltaTime;

    if ((direction > 0 && newY > targetY) ||
        (direction < 0 && newY < targetY)) {
      newY = targetY;
    }

    SetPosition({GetPosition().x, newY});
  }
}
