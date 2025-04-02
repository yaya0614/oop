#include "Pusher.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "WaterGirl.hpp"
#include <memory>
#include <string>

Pusher::Pusher() {
  SetImage(GA_RESOURCE_DIR "/Pusher/push_1.png");
  m_Transform.scale = {0.4, 0.32f};
  SetPosition({-140, -120});

  SetZIndex(25);
  m_OriginalY = GetPosition().y; // 記錄初始 Y 值
  m_TargetY = m_OriginalY - 20;  // 下降 20 單位
};

void Pusher::CheckCollisionTest(const std::shared_ptr<Collider> &collider,
                                float expect_x,
                                std::shared_ptr<MapBackground> &background,
                                int level_id, int a) {
  auto IsPushedResult = collider->IsPushedbool(expect_x, background, 0, 0);
  m_IsPushed = IsPushedResult.IsPushed;
  tag = IsPushedResult.tag;
};

void Pusher::Update(std::string LeftOrRight_fire, std::string LeftOrRight_water,
                    bool water_bool, bool fire_bool) {
  if (water_bool) {
    record_tag = LeftOrRight_water;
  } else if (fire_bool) {
    record_tag = LeftOrRight_fire;
  }

  if (record_tag == "right") {
    SetImage(GA_RESOURCE_DIR "/Pusher/push_1.png");
  } else if (record_tag == "left") {
    SetImage(GA_RESOURCE_DIR "/Pusher/push_2.png");
  }
};

void Pusher::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};
