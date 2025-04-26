#ifndef NEWWATERGIRL_HPP
#define NEWWATERGIRL_HPP
#include "actors/NewCharacter.hpp"
#include <glm/fwd.hpp>
class NewWaterGirl : public NewCharacter {
public:
  NewWaterGirl(glm::vec2 startPos);
  bool isJumping = false;
  float jumpingBuffer = 0.0f;
  const float gravity = -300.0f;
  const float jumpSpeed = 200.0f;
  const float targethigh = 9;
  void Jump();
  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms);
  void Update(float deltaTime,
              const std::vector<MapBackground::Platform> &platforms);
  virtual void OnCollideX() override;
  virtual void OnCollideY() override;
};
#endif // NEWWATERGIRL_HPP