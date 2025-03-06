#ifndef MAPBACKGROUND_HPP
#define MAPBACKGROUND_HPP

#include "MGameObject.hpp"
#include "Util/Image.hpp"
#include <Util/GameObject.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <vector>

class MapBackground : public MGameObject {
public:
  explicit MapBackground(int level_id = 0); // 修改构造函数，接受 level_id
  void SetImage(const std::string &ImagePath);

  struct Platform {
    int x1, x2, y;
  };

  struct Slope {
    int x1, x2, y1, y2;
  };

  struct Level {
    std::vector<Platform> platforms;
    std::vector<Slope> slopes;
    std::string ImagePath;
  };

  struct Boundry {
    float min_x = -401.0f;
    float max_x = 402.0f;
    float min_y = -298.0f;
    float max_y = 286.0f;
  };

  Boundry GetBoundry() const;

private:
  std::string m_ImagePath;
  int level_id;
  std::vector<Level> levels{
      // {{{100, 300, 400}, {400, 600, 500}},
      //  {{600, 700, 500, 550}},
      //  GA_RESOURCE_DIR "/Fire/boy/boy_1.png"},
      {{{100, 300, 400}, {400, 600, 500}},
       {{600, 700, 500, 550}},
       GA_RESOURCE_DIR "/Image/Background/Level1.png"},
  };
};

#endif // MAPBACKGROUND_HPP
