#include "MapBackground.hpp"
#include "Util/Image.hpp"
#include <memory>
#include <string>

MapBackground::MapBackground(int level_id) : level_id(level_id) {
  if (level_id < 0 || level_id >= levels.size()) {
    this->level_id = 0;
  }
  SetZIndex(20);
};

void MapBackground::SetImage(const std::string &ImagePath) {
  m_ImagePath = ImagePath;
  m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
};

MapBackground::Boundry MapBackground::GetBoundry() const { return Boundry{}; }

MapBackground::Level MapBackground::GetLevelData(int level_num) {
  return levels[level_num];
};

int MapBackground::GetLevelSize(int level_num) {
  return levels[level_num].platforms.size();
}