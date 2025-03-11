#ifndef MAPBACKGROUND_HPP
#define MAPBACKGROUND_HPP

#include "MGameObject.hpp"
#include <Util/GameObject.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <vector>

class MapBackground : public MGameObject {
public:
  explicit MapBackground(int level_id = 0); // 修改构造函数，接受 level_id
  void SetImage(const std::string &ImagePath);

  struct Platform {
    float x1, x2, y_low, y_high;
  };

  struct Slope {
    float x1, x2, y_low, y_high;
  };

  struct Wall {
    float x1, y1;
  };

  struct Level {
    std::vector<Platform> platforms;
    std::vector<Slope> slopes;
    std::vector<Wall> walls;
    std::vector<std::string> tag;
    std::string ImagePath;
  };

  struct Boundry {
    float min_x = -420.0f;
    float max_x = 420.0f;
    float min_y = -320.0f;
    float max_y = 320.0f;
  };

  Boundry GetBoundry() const;
  Level GetLevelData(int level_num);
  int GetLevelSize(int level_num);

private:
  std::string m_ImagePath;
  std::vector<std::string> tag;
  int level_id;
  std::vector<Level> levels{
      {
          {
              {-401.0f, -350, -322, -307.2},
              {350.0f, 433, -307.2, -210.0},
              {0.0f, 325, -192.0, -143.0},
              {-401.0f, -54, -148, -100.2},
          },
          {{-54, -11, -259, -103.0}},
          {{337.0f, -232.8f}},
          {
              "wall",
          },
          {GA_RESOURCE_DIR "/Image/Background/Level1.png"},
      },

  };
};

#endif // MAPBACKGROUND_HPP
