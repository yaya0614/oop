#ifndef NEWWATERGIRL_HPP
#define NEWWATERGIRL_HPP
#include "actors/NewCharacter.hpp"
#include "actors/NewRock.hpp"
#include "machines/NewBridge.hpp"
#include "machines/NewDoor.hpp"
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
  void SetDoor(const std::vector<std::shared_ptr<NewDoor>> &door);
  void SetPool(const std::vector<std::shared_ptr<NewPool>> &pools) {
    pool = pools;
  }
  void SetBridge(const std::vector<std::shared_ptr<NewBridge>> &bridge);

private:
  std::vector<std::shared_ptr<NewElevator>> elevators;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<NewPool>> pool;
  std::vector<std::shared_ptr<NewBridge>> bridges;
  std::shared_ptr<NewRock> rocks;
  bool isOnElevator = true;
  bool isOnRock = false;
};
#endif // NEWWATERGIRL_HPP