#ifndef NEWSWITCH_HPP
#define NEWSWITCH_HPP

#include "NewMachine.hpp"
#include "Util/Logger.hpp"
#include "machines/NewElevator.hpp"
#include <Util/Image.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <string>
#include <vector>
class NewSwitch : public NewMachine {
public:
  NewSwitch(glm::vec2 startpos, glm::vec2 size, std::string color,
            bool IsButton);
  void IsCollider(std::shared_ptr<NewCharacter> character1,
                  std::shared_ptr<NewCharacter> character2,
                  std::vector<std::shared_ptr<NewElevator>> elevators,
                  float dealtatime);

private:
  bool activated = false;

  bool IsButton; // 判斷該元件是btn還是lever
  std::string color;
  int current_lever_dir = 0; // 預設current_lever_dir在右邊所以是1

  void ChangeButtonImage(); // 換圖片的內部函式（你自己定義）
  void ChangeLeverImage(int dir);
  void ActivateElevator(float dealtatime, bool activate,
                        std::vector<std::shared_ptr<NewElevator>> elevators);
};

#endif
