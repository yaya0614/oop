#include "machines/NewDoor.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "machines/NewMachine.hpp"
#include <memory>
NewDoor::NewDoor(glm::vec2 startpos, glm::vec2 size, std::string color)
    : NewMachine(startpos, size, color) {
  this->startpos = startpos;
  this->color = color;
  self_tag = color;
  this->size = size;

  m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/DoorAnimation/" +
                                             color + "_door/" + "door_1.png");
  m_Transform.scale = {0.46, 0.5f};
  SetPosition(startpos);
  SetVisible(true);
  SetZIndex(80);
  AnimationPaths = {
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_1.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_2.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_3.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_4.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_5.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_6.png",
      GA_RESOURCE_DIR "/DoorAnimation/" + color + "_door/" + "door_7.png",
  };
  animation =
      std::make_shared<Util::Animation>(AnimationPaths, false, 300, false, 0);
};

void NewDoor::PlayAnimation() {
  this->animation->Play();
  SetDrawable(this->animation);
};

bool NewDoor::IsCollider(std::shared_ptr<NewCharacter> c1) {
  glm::vec2 pos = {c1->position.x, c1->position.y + c1->offest};
  int character_middle = pos.x;
  int character_bottom = pos.y - c1->size.y / 2;

  return (character_middle >= (startpos.x - size.x) &&
          character_middle <= (startpos.x + size.x) &&
          character_bottom - (startpos.y - size.y) >= 0.5 &&
          character_bottom - (startpos.y - size.y) <= 2);
};
bool NewDoor::IsCharacterMatch(std::shared_ptr<NewCharacter> c1) {

  if (IsCollider(c1)) {
    if (c1->tag == self_tag) {
      return true;
    }
  }
  return false;
};

//
void NewDoor::IsCharacterInto(std::shared_ptr<NewCharacter> c1,
                              std::shared_ptr<NewCharacter> c2) {
  if ((IsCollider(c1) && c1->tag == self_tag) ||
      (IsCollider(c2) && c2->tag == self_tag)) {
    if (!IsOpen) {
      IsOpen = true;
      PlayAnimation();
    }
  }
}

int NewDoor::GetCurrentAnimation() {
  return this->animation->GetCurrentFrameIndex();
};
