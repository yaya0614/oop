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
          {{{-380, 380, -295, -286}, // 底部平台
            {-380, 380, 270, 280},   // 上方平台（增加厚度）
            {-380, -380, -300, 300}, // 左牆（防掉出左邊）
            {380, 380, -300, 300},   // 右牆（防掉出右邊）
            {-380, -135, -223, -204},
            {320, 380, -285, -225},
            {-11, 280, -184, -165},
            {-49, -10, -165, -120},
            {-380, -51, -140, -120},
            {-295, 95, -42, -19},
            {34, 380, -58, -40},
            // {30, 257, -57, -40},
            // {257, 380, -57, -40},
            {196, 298, 25, 67},
            {198, 196, 64, 108},
            {12, 177, 45, 108},
            {-278, 11, 45, 66},
            {-380, -279, 45, 147},
            {-192, -110, 168, 209},
            {-380, -279, 45, 147},
            {-192, -110, 168, 209},
            {-151, -51, 118, 169},
            {-51, 380, 155, 169},
            {324, 380, -122, -59}

          }

          },
      },
      {
          {{
              {-370, 370, -288, -270}, // 底部平台
              {-370, 370, 270, 270},   // 上方平台（增加厚度）
              {-370, -370, -270, 270}, // 左牆（防掉出左邊）
              {370, 370, -270, 270},   // 右牆（防掉出右邊）
              {-232, -88, -225, -210}, {0, 141, -225, -210},
              {245, 305, -288, -228},  {294, 328, -288, -209},

              {328, 370, -209, -170},  {-311, 270, -131, -109},
              {-370, -311, -110, -52}, {-267, -229, -30, -11}, // 第一個斜波
              {-190, -170, 29, 48},    {-105, -67, 70, 91},
              {-65, 92, -29, -11},     {-228, 69, -29, -11},
              {93, 271, -29, -11}, // 沼澤範圍
              {-49, 68, -29, 11},      {137, 174, 31, 49},
              {275, 313, -32, 49},     {313, 370, 49, 110},
              {212, 251, 150, 171},    {73, 209, 171, 191},
              {-370, -49, 171, 191},

          }

          },
      }

  };
};
#endif // MAPBACKGROUND_HPP