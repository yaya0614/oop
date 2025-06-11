#ifndef TEXT_HPP
#define TEXT_HPP
#include "MGameObject.hpp"
#include "Util/Logger.hpp"
#include "Util/Text.hpp"
#include <string>

class Text : public MGameObject {
public:
  Text(int DiamondAmount)
      : MGameObject(std::make_unique<Util::Text>(

                        GA_RESOURCE_DIR "/Font/NotoSansTC-Bold.ttf", 25,
                        std::to_string(DiamondAmount),
                        Util::Color::FromName(Util::Colors::YELLOW)),
                    100) {}

  ~Text() override = default;

  void Start(){};

  void Update();

private:
  std::string m_Font;
  int m_Size;
  std::shared_ptr<Util::Text> m_Text;
};
#endif