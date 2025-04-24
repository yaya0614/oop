#ifndef MAPBACKGROUND_HPP
#define MAPBACKGROUND_HPP

#include "MGameObject.hpp"
#include "elevation.hpp"
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
  struct Button {
    float x1, x2, y_low, y_high;
  };

  // 之後做優化的時候，合併所有機關包括：按鈕跟推桿=>
  // 用機關的英文做宣告然後在Collier共用一個function個用tag做區別
  struct Push {
    float x1, x2, y_high;
  };

  struct Wall {
    float x1, y1;
  };

  struct Pool {
    float x1, x2, y_low, y_high, expect_fall_down_h;
    std::string tag;
  };

  struct Elevation {
    float x1, x2, y_low, y_high;
  };

  struct Level {
    std::vector<Platform> platforms;
    std::vector<Slope> slopes;
    std::vector<Button> buttons;
    std::vector<Push> pushers;
    std::vector<Elevation> elevations;
    std::vector<Pool> pools;
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
              {-401.0f, -350, -322, -308.13},
              {360.0f, 440, -309, -210.0},
              {0.0f, 330, -192.0, -143.0},
              {-401.0f, -25, -148, -100.2},
              {-311.0f, 50, -30, 14},
              {52, 450, -40, -10},
              {220, 360, -28, 100},
              {30, 220, 100, 145},
              {-250, 30, 61, 100},
              {-401.0f, -295, 61, 180},
              {-206, -120, 198, 230},
              {-119, 403, 198, 205},

          },
          {{-54, -11, -259, -103.0}},
          {{95, 104, -38, -48}, {222, 278, 50, 61.87}},
          {{-162, -118, -140}},
          // pusher original {95, 104, -48.95},
          {{
              -401,
              -312,
              -119,
              -99,
          }},
          {{-22, 65, -322, -309, -276.2f, "ice"},
           {130, 170, -322, -309, -276.2f, "fire"}},
          {{337.0f, -232.8f}},
          {
              "wall",
          },
          // {GA_RESOURCE_DIR "/Image/Background/Level1.png"},
      },
      {
          {{
              {-380, 380, -295, -284}, // 底部平台
              {-380, 380, 270, 280},   // 上方平台（增加厚度）
              {-380, -380, -300, 300}, // 左牆（防掉出左邊）
              {380, 380, -300, 300},   // 右牆（防掉出右邊）
              {320, 380, -285, -225},
              {-11, 280, -184, -165},
              {-49, -10, -165, -120},
              {-380, -51, -140, -123},
              {-295, -30, -40, -20},

              // {-10, 300, -162, -132},
              // {-370, -10, -132, -90},

          }

          },
      }

  };
};
#endif // MAPBACKGROUND_HPP