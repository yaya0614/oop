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
    float x1, x2, y;
  };

  struct Slope {
    float x1, y1, x2, y2;
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
          {{332.8f, 420, -232.8f}},
          {{337, -259, 360, -234}},
          {{337.0f, -232.8f}},
          {
              "wall",
          },
          {GA_RESOURCE_DIR "/Image/Background/Level1.png"},
      },
      // {{{100, 300, 400}, {400, 600, 500}},
      //  {{600, 700, 500, 550}},
      //  GA_RESOURCE_DIR "/Fire/boy/boy_1.png"},
      // {{{360, 420, -237}, {400, 600, 500}},
      //  {{336, -259, 360, -235}},
      //  GA_RESOURCE_DIR "/Image/Background/Level1.png"},
  };
};

#endif // MAPBACKGROUND_HPP
