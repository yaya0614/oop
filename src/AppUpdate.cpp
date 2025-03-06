#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Update() {
  // LOG_DEBUG("...");
  // TODO: Add your own logics to finish the tasks in README.md

  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
    if (start_btn) {
      int x = start_btn->GetPosition().x;
      int y = start_btn->GetPosition().y;
      if (mousePos.x - x < 30 && mousePos.y - y < 30) {
        m_PRM->IsPressed();
        start_btn->SetVisible(false);
        start_btn.reset();
      }
    }
  }
  // float expect_x = Fire_boy->GetPosition().x;
  // float expect_y = Fire_boy->GetPosition().y;

  // if (Util::Input::IsKeyPressed(Util::Keycode::W)) { // 上
  //   expect_y += 2;
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::S)) { // 下
  //   expect_y -= 3;
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::D)) { // 右
  //   expect_x += 3;
  // }
  // if (Util::Input::IsKeyPressed(Util::Keycode::A)) { // 左
  //   expect_x -= 3;
  // }

  // // 如果移動後不會超出邊界，才真正移動
  // if (!Fire_boy->IsOverlines(expect_x, expect_y, m_PRM)) {
  //   Fire_boy->SetPosition({expect_x, expect_y});
  // }

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
