#include "FireSea.hpp"
#include "Collider.hpp"
#include "FireBoy.hpp"
#include "Util/Logger.hpp"
FireSea::FireSea() {
  SetPosition({170, -310});
  SetZIndex(100);
  m_Transform.scale = {0.6, 0.43};
  SetVisible(true);
  m_Drawable =
      std::make_shared<Util::Animation>(AnimationPaths, false, 200, false, 0);
};
bool FireSea::IfAnimationEnds() const {
  auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
  return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}
// bool FireSea::IsPlayerFall(std::shared_ptr<FireBoy> &player) {
//   float player_x = player->GetPosition().x;

//   if ((player_x >= 122) & (player_x <= 212)) {
//     LOG_DEBUG("進入火池");
//   } else {
//     LOG_DEBUG("未進入池");
//   }
// };