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

  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);

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
  float deltaTime = 1.0 / 60.0f;
  fire_boy->Update(deltaTime, mapbackground);

  float expect_x = fire_boy->GetPosition().x;
  float expect_y = fire_boy->GetPosition().y;
  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    fire_boy->Jump();
  }

  // GetPosition 是抓物體的正中心
  // SetPosition 是以物體中心的.x設 物體最底的.y設

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) { // 右
    expect_x += 2;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) { // 左
    expect_x -= 2;
  }

  if (!fire_boy->IsOverLines(expect_x, expect_y, mapbackground)) {
    bool collided = false;

    for (int i = 0; i < mapbackground->GetLevelData(0).platforms.size(); i++) {
      if (fire_boy->IsCollider(expect_x, expect_y, mapbackground, 0, i)) {
        LOG_DEBUG(i);
        collided = true;
        collidedPlatformIndex = i;
        break;
      }
    }

    if (!collided) {
      fire_boy->SetPosition({expect_x, expect_y});
    } else {
    }
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
