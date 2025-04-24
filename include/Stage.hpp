#ifndef STAGE_HPP
#define STAGE_HPP
#include "MGameObject.hpp"

class Stage : public MGameObject {
public:
  explicit Stage();
  void SetImage(const std::string &ImagePath);

private:
  std::string m_ImagePath;
};
#endif