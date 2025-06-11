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
  void Update();
  int GetDiamondAmonut();
  std::string tag;
  bool isCollected;

private:
  int diamond_amount = 0;
  float target_size = 0.4f;
  int scaleIndex = 0;      // 目前正在用哪個 scale
  float scaleTimer = 0.0f; // 用來計時更新間隔

  std::vector<float> dim_size = {
      0.45f, 0.44f, 0.43f, 0.42f, 0.41f, 0.4f,
  }; // 像閃爍的變化值
};
#endif // DIAMOND_HPP