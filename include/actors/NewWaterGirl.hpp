#ifndef NEWWATERGIRL_HPP
#define NEWWATERGIRL_HPP
#include "actors/NewCharacter.hpp"
#include "actors/NewRock.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"
#include <glm/fwd.hpp>
class NewWaterGirl : public NewCharacter,
                     public std::enable_shared_from_this<NewWaterGirl> {
public:
  NewWaterGirl(glm::vec2 startPos);

  void Jump();
  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms);
  void Update(float deltaTime,
              const std::vector<MapBackground::Platform> &platforms);
  virtual void OnCollideX() override;
  virtual void OnCollideY() override;
  virtual void ChangeStatus(std::string status) override;

  void
  SetElevators(const std::vector<std::shared_ptr<NewElevator>> &elevatorsList);
  void SetRock(const std::shared_ptr<NewRock> &rocks);
  void SetPool(const std::vector<std::shared_ptr<NewPool>> &pools) {
    pool = pools;
  }

private:
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewPool>> pool;
  std::shared_ptr<NewRock> rocks;
  bool isOnElevator = true;
};
#endif // NEWWATERGIRL_HPP