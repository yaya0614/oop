#include "Collider.hpp"
#include "Util/Logger.hpp"

bool Collider::IsOverLines(float expect_x, float expect_y,
                           std::shared_ptr<MapBackground> &background) {
  float player_min_x = expect_x - GetScaledSize().x / 2;
  float player_max_x = expect_x + GetScaledSize().x / 2;
  float player_min_y = expect_y - GetScaledSize().y / 2;
  float player_max_y = expect_y + GetScaledSize().y / 2;

  float min_x = background->GetBoundry().min_x;
  float max_x = background->GetBoundry().max_x;
  float min_y = background->GetBoundry().min_y;
  float max_y = background->GetBoundry().max_y;

  if (player_max_x > max_x || player_min_x < min_x || player_max_y > max_y ||
      player_min_y < min_y) {
    return true;
  } else {
    return false;
  }
};

/*
  Update(會一直觸發)->
  在每個IsPressed(KeyCode)之前要做預測角色是否可以移動，所以先記下expect_x、expect_y表示當前玩家的位置加上未來要觸發的
  WAD 會是多少位移量
  -> 丟進第一層 IsOverLines（整個地圖最外的邊界判斷） ->
  如果為未觸碰到邊界即觸發
  IsCollider()判斷是否有觸發地圖的障礙物，因為障礙物有很多個所以用for(以障礙物陣列的長度做range)來跑
  這樣就可以配對到是否有符合當前狀態的最近障礙物。若有障礙物則不可移動（AD位移量+0）；反之則觸發（WA、WD）讓人物跳到障礙物上SetPosition
*/

// bool Collider::IsCollider(float expect_x, float expect_y,) {

//   float player_min_x = expect_x - GetScaledSize().x / 2;
//   float player_max_x = expect_x + GetScaledSize().x / 2;
//   float player_min_y = expect_y - GetScaledSize().y / 2;
//   float player_max_y = expect_y + GetScaledSize().y / 2;
// };