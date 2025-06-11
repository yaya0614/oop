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
  virtual void
  Update(float deltaTime,
         const std::vector<MapBackground::Platform> &platforms) override;
  void ChangeStatus(std::string status);
};
#endif // NEWWATERGIRL_HPP