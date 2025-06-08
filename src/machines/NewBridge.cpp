#include "machines/NewBridge.hpp"
#include "Util/Logger.hpp"
#include "actors/NewCharacter.hpp"
#include "machines/NewMachine.hpp"

NewBridge::NewBridge(glm::vec2 startpos, glm::vec2 size, glm::vec2 scale,
                     std::string tag, int Zindex)
    : NewMachine(startpos, size, "bridge") {
  SetPosition(startpos);
  SetZIndex(Zindex);
  m_Transform.scale = {scale.x, scale.y};
  m_Drawable = std::make_shared<Util::Image>(
      "/Users/mel/Desktop/oop/Resources/Bridge/" + tag + ".png");
  SetVisible(true);
};

float NewBridge::GetAngle() { return angle; }

void NewBridge::Update(float deltaTime, const std::shared_ptr<NewCharacter> c1,
                       const std::shared_ptr<NewCharacter> c2) {
  bool FbOnBridge = IsCollidingWithMachine(c1);
  bool WgOnBridge = IsCollidingWithMachine(c2);

  float centerX = startPos.x;
  float maxDistance = size.x / 2.0f;
  float totalAngleFactor = 0.0f;
  int count = 0;

  if (FbOnBridge) {
    float offset = c1->GetPosition().x - centerX;
    float distanceFactor = 1.0f - std::abs(offset) / maxDistance;
    float direction = (offset != 0.0f) ? offset / std::abs(offset) : 0.0f;
    totalAngleFactor += distanceFactor * direction;
    count++;
  }

  if (WgOnBridge) {
    float offset = c2->GetPosition().x - centerX;
    float distanceFactor = 1.0f - std::abs(offset) / maxDistance;
    float direction = (offset != 0.0f) ? offset / std::abs(offset) : 0.0f;
    totalAngleFactor += distanceFactor * direction;
    count++;
  }

  if (count > 0) {
    float avgAngleFactor = totalAngleFactor / count;
    targetAngle = avgAngleFactor * 0.86f;
  } else {
    targetAngle = 0.0f;
  }

  angle += (targetAngle - angle) * 0.8f * deltaTime;
  m_Transform.rotation = {angle};
}
