#ifndef DIAMOND
#define DIAMOND

#include "MGameObject.hpp"
#include <memory>
#include <string>
class Diamond : public MGameObject {
public:
  Diamond(glm::vec2 pos, std::string tag);
  void Collect();
  void DisableShow();
  bool IsCollected() const;
  std::string tag;
  bool isCollected;

private:
};
#endif // DIAMOND_HPP