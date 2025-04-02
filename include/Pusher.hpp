#ifndef PUSHER_HPP
#define PUSHER_HPP

#include "Collider.hpp"
#include "MGameObject.hpp"
#include "WaterGirl.hpp"
#include <glm/fwd.hpp>

class Pusher : public MGameObject {
public:
  explicit Pusher();
  void SetImage(const std::string &ImagePath);
  void CheckCollision(const std::shared_ptr<WaterGirl> &watergirl,
                      float expect_x,
                      std::shared_ptr<MapBackground> &background, int level_id,
                      int a);

  void CheckCollisionTest(const std::shared_ptr<Collider> &collider,
                          float expect_x,
                          std::shared_ptr<MapBackground> &background,
                          int level_id, int a);
  void Update(std::string LeftOrRight_fire, std::string LeftOrRight_water,
              bool water_bool, bool fire_bool);

private:
  std::string m_ImagePath;
  bool m_IsPushed = false;

  std::string tag = "none";
  float m_TargetY;
  std::string record_tag;

  float m_OriginalY;
};
#endif