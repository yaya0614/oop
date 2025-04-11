#include "pages/FirstLevel.hpp"
#include "Util/Input.hpp"

void FirstLevel::Start() {
  fire_boy = std::make_shared<FireBoy>();
  fire_boy->m_Transform.scale = {0.4, 0.41f};
  m_Root.AddChild(fire_boy);

  water_girl = std::make_shared<WaterGirl>();
  water_girl->m_Transform.scale = {0.4, 0.41f};
  m_Root.AddChild(water_girl);

  ice_sea = std::make_shared<AnimatedCharacter>(std::vector<std::string>{
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_1.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_2.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_3.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_4.png",
      GA_RESOURCE_DIR "/IceGirl/ice_small/water_5.png",
  });
  ice_sea->SetPosition({20, -310});
  ice_sea->SetZIndex(100);
  ice_sea->m_Transform.scale = {0.7, 0.43};
  ice_sea->SetVisible(true);
  m_Root.AddChild(ice_sea);

  m_fireSea = std::make_shared<FireSea>();
  m_Root.AddChild(m_fireSea);

  ele_blue = std::make_shared<Elevation>();
  m_Root.AddChild(ele_blue);

  rock = std::make_shared<Rock>();
  m_Root.AddChild(rock);

  ele_purple = std::make_shared<ElevationPurple>();
  m_Root.AddChild(ele_purple);

  button_top = std::make_shared<ButtonTop>();
  m_Root.AddChild(button_top);

  button = std::make_shared<Button>();
  m_Root.AddChild(button);

  pusher = std::make_shared<Pusher>();
  m_Root.AddChild(pusher);

  firedoor = std::make_shared<FireDoor>();
  m_Root.AddChild(firedoor);

  waterdoor = std::make_shared<WaterDoor>();
  m_Root.AddChild(waterdoor);

  // {-22, 65, -322, -309, -276.2f, "ice"},
  // {122, 212, -322, -309, -276.2f, "fire"}},
  std::vector<glm::vec2> redDiamondPositions = {
      {167, -260},
      {-250, 20},
      {-175, 250},
      {0, 200},

  };

  std::vector<glm::vec2> waterDiamondPositions = {
      {20, -260},
      {200, -20},
      {-380, 190},
      {100, 200},

  };
  for (auto &pos : redDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "fire");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  for (auto &pos : waterDiamondPositions) {
    auto diamond = std::make_shared<Diamond>(pos, "water");
    diamonds.push_back(diamond);
    m_Root.AddChild(diamond);
  }

  mapbackground = std::make_shared<MapBackground>();
  m_Root.AddChild(mapbackground);

  m_CurrentState = State::UPDATE;
};
void FirstLevel::Update() {

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

  auto IsPress_w = water_girl->IsPressedButtonbool(
      expect_x_water_girl, expect_y_water_girl, mapbackground, 0, 0);

  auto IsPress =
      fire_boy->IsPressedButtonbool(expect_x, expect_y, mapbackground, 0, 0);

  button->Update(deltaTime, IsPress.IsPushed || IsPress_w.IsPushed,
                 IsPress_w.num, IsPress.num);

  button_top->Update(deltaTime, IsPress.IsPushed || IsPress_w.IsPushed,
                     IsPress_w.num, IsPress.num);
  ele_purple->Update(deltaTime, IsPress.IsPushed || IsPress_w.IsPushed);
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

  bool tag_fb = firedoor->IsWaterInto(water_girl, water_girl->GetHalfHeight());
  firedoor->Update(tag_fb);

  bool tag_wt = waterdoor->IsWaterInto(fire_boy, fire_boy->GetHalfHeight());
  waterdoor->Update(tag_wt);
  water_girl->Die(firedoor->GetIsOpen());
  fire_boy->Die(waterdoor->GetIsOpen());

  auto water_rock = rock->CheckCollision(water_girl->GetPosition(),
                                         water_girl->GetHalfWidth(),
                                         water_girl->GetHalfHeight());
  auto fire_rock =
      rock->CheckCollision(fire_boy->GetPosition(), fire_boy->GetHalfWidth(),
                           fire_boy->GetHalfHeight());
  rock->Update(fire_rock.tag, water_rock.tag, fire_rock.PushSide,
               water_rock.PushSide);

  for (auto &diamond : diamonds) {
    if (diamond->IsCollected())
      continue;

    if (diamond->tag == "fire" && fire_boy->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }

    if (diamond->tag == "water" && water_girl->IsCollidingWith(*diamond)) {
      diamond->SetVisible(false);
      diamond->isCollected = true;
      diamond->DisableShow();
    }
  }

  if (firedoor->GetIsOpen() && waterdoor->GetIsOpen()) {
    LOG_CRITICAL("遊戲結束");
  }

  if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
      Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }

  m_Root.Update();
};
void FirstLevel::End(){

};