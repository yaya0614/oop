#include "machines/NewPool.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "machines/NewMachine.hpp"
#include <glm/fwd.hpp>
#include <memory>

NewPool::NewPool(glm::vec2 startpos, glm::vec2 size, std::string color,
                 glm::vec2 scale)
    : NewMachine(startpos, size, color) {
  this->color = color;
  self_tag = color;
  this->size = size;
  //   this->startpos = startpos;
  const std::vector<std::string> AnimationPaths = {
      GA_RESOURCE_DIR "/Pool/" + color + "/" + color + "_1.png",
      GA_RESOURCE_DIR "/Pool/" + color + "/" + color + "_2.png",
      GA_RESOURCE_DIR "/Pool/" + color + "/" + color + "_3.png",
      GA_RESOURCE_DIR "/Pool/" + color + "/" + color + "_4.png",

  };
  SetPosition(startpos);
  SetZIndex(80);
  m_Transform.scale = {scale.x, scale.y};
  SetVisible(true);
  //   m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Pool/" +
  //   color +
  //  "/" + color + "_1.png");
  m_Drawable =
      std::make_shared<Util::Animation>(AnimationPaths, false, 200, false, 0);
};

std::string NewPool::IsCharacterFall(std::shared_ptr<NewCharacter> c1) {
  // 先判斷是否有碰撞
  // LOG_DEBUG("test");
  bool IsColliderC1 = IsCollidingWithMachine(c1);

  if (IsColliderC1) {
    return self_tag;
  }
  return "no";
};