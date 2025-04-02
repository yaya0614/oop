#include "AnimatedCharacter.hpp"
#include "App.hpp"
#include "Collider.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "WaterGirl.hpp"
#include "elevation.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

void App::Update() {
  glm::vec2 mousePos = Util::Input::GetCursorPosition();

  if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    LOG_DEBUG(mousePos);
  }

  if (!ice_sea->IsLooping()) {
    ice_sea->SetLooping(true);
  }

  if (!m_fireSea->IsLooping()) {
    m_fireSea->SetLooping(true);
  }

  float deltaTime = 1.0 / 60.0f;
  fire_boy->Update(deltaTime, mapbackground, ele_blue, ele_purple, rock);
  water_girl->Update(deltaTime, mapbackground, ele_blue, ele_purple, rock);

  float expect_x = fire_boy->GetPosition().x;
  float expect_y = fire_boy->GetPosition().y;

  float expect_x_water_girl = water_girl->GetPosition().x;
  float expect_y_water_girl = water_girl->GetPosition().y;
  if (Util::Input::IsKeyDown(Util::Keycode::W)) {
    fire_boy->Jump();
  }

  if (Util::Input::IsKeyDown(Util::Keycode::UP)) {
    water_girl->Jump();
  }

  bool IsPress_w = water_girl->IsPressedButtonbool(
      expect_x_water_girl, expect_y_water_girl, mapbackground, 0, 0);

  bool IsPress =
      fire_boy->IsPressedButtonbool(expect_x, expect_y, mapbackground, 0, 0);

  button->Update(deltaTime, IsPress || IsPress_w);
  ele_purple->Update(deltaTime, IsPress || IsPress_w);
  auto WaterGirl_PushData =
      water_girl->IsPushedbool(expect_x_water_girl, mapbackground, 0, 0);
  auto FireBoy_PushData = fire_boy->IsPushedbool(expect_x, mapbackground, 0, 0);

  ele_blue->Update(deltaTime, FireBoy_PushData.tag, WaterGirl_PushData.tag,
                   WaterGirl_PushData.IsPushed, FireBoy_PushData.IsPushed);
  pusher->Update(FireBoy_PushData.tag, WaterGirl_PushData.tag,
                 WaterGirl_PushData.IsPushed, FireBoy_PushData.IsPushed);

  if (Util::Input::IsKeyPressed(Util::Keycode::D)) { // 右
    expect_x += 2;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::A)) { // 左
    expect_x -= 2;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) { // 左
    expect_x_water_girl += 2;
  }
  if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) { // 右
    expect_x_water_girl -= 2;
  }

  if (!fire_boy->IsOverLines(expect_x, expect_y, mapbackground)) {
    bool collided = false;
    int collidedPlatformIndex = -1;
    for (int i = 0; i < mapbackground->GetLevelData(0).platforms.size(); i++) {
      if (fire_boy->IsCollider(expect_x, expect_y, mapbackground, 0, i)) {
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

  if (!water_girl->IsOverLines(expect_x_water_girl, expect_y_water_girl,
                               mapbackground)) {
    bool collided = false;
    int collidedPlatformIndex = -1;
    for (int i = 0; i < mapbackground->GetLevelData(0).platforms.size(); i++) {
      if (water_girl->IsCollider(expect_x_water_girl, expect_y_water_girl,
                                 mapbackground, 0, i)) {
        collided = true;
        collidedPlatformIndex = i;
        break;
      }
    }

    if (!collided) {
      water_girl->SetPosition({expect_x_water_girl, expect_y_water_girl});
    } else {
    }
  }

  bool tag = firedoor->IsWaterInto(water_girl, water_girl->GetHalfHeight());
  firedoor->Update(tag);
  water_girl->Die(firedoor->GetIsOpen());

  auto water_rock = rock->CheckCollision(water_girl->GetPosition(),
                                         water_girl->GetHalfWidth(),
                                         water_girl->GetHalfHeight());
  auto fire_rock =
      rock->CheckCollision(fire_boy->GetPosition(), fire_boy->GetHalfWidth(),
                           fire_boy->GetHalfHeight());
  rock->Update(fire_rock.tag, water_rock.tag, fire_rock.PushSide,
               water_rock.PushSide);

  if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
      Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }

  m_Root.Update();
}
