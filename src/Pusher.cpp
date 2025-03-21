#include "Pusher.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "WaterGirl.hpp"
#include <memory>

Pusher::Pusher() {
  SetImage(GA_RESOURCE_DIR "/Pusher/push_2.png");
  m_Transform.scale = {0.4, 0.32f};
  SetPosition({100, -35});
  SetZIndex(25);
  m_OriginalY = GetPosition().y; // 記錄初始 Y 值
  m_TargetY = m_OriginalY - 20;  // 下降 20 單位
};

void Pusher::CheckCollision(const std::shared_ptr<WaterGirl> &watergirl,
                            float expect_x,
                            std::shared_ptr<MapBackground> &background,
                            int level_id, int a) {
  auto IsPushedResult = watergirl->IsPushedbool(expect_x, background, 0, 0);
  // LOG_ERROR(IsPushedResult.IsPushed);
  m_IsPushed = IsPushedResult.IsPushed;
  tag = IsPushedResult.tag;
};

void Pusher::Update(float deltaTime) {
  if (m_IsPushed) {
    if (tag == "right") {
      SetImage(GA_RESOURCE_DIR "/Pusher/push_1.png");
    } else if (tag == "left") {
      SetImage(GA_RESOURCE_DIR "/Pusher/push_2.png");
    }
  }
};
void Pusher::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};
