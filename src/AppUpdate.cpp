#include "AnimatedCharacter.hpp"
#include "App.hpp"
#include <iostream>

#include "Collider.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include <string>
using namespace std;

void App::Update() {
  // LOG_DEBUG("...");
  // TODO: Add your own logics to finish the tasks in README.md

  glm::vec2 mousePos = Util::Input::GetCursorPosition();
  // auto a = mapbackground->GetLevelData(0).tag[0];
  // LOG_DEBUG(a);

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos.x);

    // if (start_btn) {
    //   int x = start_btn->GetPosition().x;
    //   int y = start_btn->GetPosition().y;
    //   if (mousePos.x - x < 30 && mousePos.y - y < 30) {
    //     m_PRM->IsPressed();
    //     start_btn->SetVisible(false);
    //     start_btn.reset();
    //   }
    // }
  }

  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    fire_boy->Jump();
  }

  float deltaTime = 1.0f / 60.0f;
  float ground = fire_boy->GetPosition().y - 1;

  // LOG_DEBUG(ground);
  // LOG_DEBUG(fire_boy->GetPosition().y);
  fire_boy->Update(deltaTime);
  float expect_x = fire_boy->GetPosition().x;
  float expect_y = fire_boy->GetPosition().y;

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) { // 右
    expect_x += 2;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) { // 左
    expect_x -= 2;
  }

  if (!fire_boy->IsOverLines(expect_x, expect_y, mapbackground)) {
    // 不會出界 fire_boy->SetPosition({expect_x, expect_y});
    for (auto check_str : mapbackground->GetLevelData(0).tag) {
      if (check_str == "wall") {
        auto wall = mapbackground->GetLevelData(0).walls[0];
        float player_x = expect_x + fire_boy->GetScaledSize().x / 2;
        float player_y = expect_y + fire_boy->GetScaledSize().y / 2;

        LOG_DEBUG("player_x", player_x);
        float wall_x = wall.x1;
        float wall_y = wall.y1;

        if (!(player_x > wall_x && player_y == wall_y)) {
          fire_boy->SetPosition({expect_x, expect_y});
        }
        LOG_DEBUG(player_x);
        if ((player_x >= mapbackground->GetLevelData(0).platforms[0].x1) &&
            (player_x <= mapbackground->GetLevelData(0).platforms[0].x2) &&
            (fire_boy->GetGround() <=
             mapbackground->GetLevelData(0).platforms[0].y) &&
            fire_boy->GetJump()) {

          fire_boy->Setter(mapbackground->GetLevelData(0).platforms[0].y + 20);
        };
      }
    }
  }

  if (m_Phase == Phase::BEE_ANIMATION) {
    m_Bee->SetLooping(true);
  }
  if (m_Phase == Phase::COUNTDOWN) {
    m_Ball->SetLooping(true);
  }

  /*
   *  Do not touch the code below as they serve the purpose for validating the
   * tasks, rendering the frame, and exiting the game.
   */

  if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
      Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }

  if (m_EnterDown) {
    if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
      ValidTask();
    }
  }
  m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

  m_Root.Update();
}
