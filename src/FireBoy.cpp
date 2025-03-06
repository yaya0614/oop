#include "FireBoy.hpp"
#include "Util/Image.hpp"

FireBoy::FireBoy(const std::string &ImagePath) {
  SetImage(ImagePath);

  ResetPosition();
}

void FireBoy::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;

  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}
