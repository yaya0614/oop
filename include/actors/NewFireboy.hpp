#pragma once
#ifndef NEWFIREBOY_HPP
#define NEWFIREBOY_HPP
#include "NewCharacter.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "actors/NewRock.hpp"
#include "machines/NewBridge.hpp"
#include "machines/NewDoor.hpp"
#include "machines/NewElevator.hpp"
#include "machines/NewPool.hpp"

#include <memory>
#include <string>
#include <vector>

class NewFireBoy : public NewCharacter,
                   public std::enable_shared_from_this<NewFireBoy> {
public:
  NewFireBoy(glm::vec2 startPos);
  virtual void
  Update(float deltaTime,
         const std::vector<MapBackground::Platform> &platforms) override;
  void ChangeStatus(std::string status);
};

#endif
