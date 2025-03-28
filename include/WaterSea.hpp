#ifndef WATERSEA_HPP
#define WATERSEA_HPP

#include "MGameObject.hpp"
#include "Util/Animation.hpp"
class WaterSea : public MGameObject {

public:
  explicit WaterSea();
  void SetImage(std::string &AnimationPaths);
};

#endif