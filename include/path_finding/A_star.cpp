#include <algorithm>
#include <map_system.h>
#include <memory>
#include <path_finding.h>
#include <queue>
#include <utils.h>
#include <vector>

using namespace utils::distance;

namespace path_finding {
namespace A_star {

std::vector<point> find_path(const i_path_context &ctx, point start, point end,
                             bool dir_8) {
  return path_finder(ctx).find_path(start, end, dir_8);
}

void path_finder::init(point start, point end, bool dir_8) {
  open_list = {};
  for (int i = 0; i < ctx.get_height(); i++) {
    closed_list[i].assign(ctx.get_width(), nullptr);
  }

  auto start_node = std::make_shared<node>(start, nullptr, 0.0f,
                                           manhattan_plus(start, end, dir_8));
  open_list.push(start_node);
}

std::vector<point> path_finder::find_path(point start, point end, bool dir_8) {
  init(start, end, dir_8);

  while (!open_list.empty()) {
    auto curr = open_list.top();
    open_list.pop();

    // 检查closed_list中是否存在更优路径
    if (closed_list[curr->y][curr->x] &&
        closed_list[curr->y][curr->x]->g <= curr->g)
      continue;

    // 检查是否到达终点
    if (*curr == end) {
      // 重构路径
      std::vector<point> path;
      auto node = curr;
      while (node) {
        path.push_back(*node);
        node = node->parent;
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    // 将当前节点加入 closed_list
    closed_list[curr->y][curr->x] = curr;

    int dir_count = dir_8 ? 8 : 4;
    for (int i = 0; i < dir_count; i++) {
      int nx = curr->x + EDIR_TO_DIR[i].x;
      int ny = curr->y + EDIR_TO_DIR[i].y;
      point np = {nx, ny};

      if (!ctx.is_walkable(np))
        continue;

      float new_g = curr->g + ctx.get_cost(np) * EDIR_TO_DIR[i].dist_scale;
      // 查找closed_list 中是否以及存储该节点
      // 如果存在更优路径
      if (closed_list[ny][nx] && closed_list[ny][nx]->g <= new_g)
        continue;

      auto next = std::make_shared<node>(np, curr, new_g,
                                         manhattan_plus(np, end, dir_8));
      open_list.push(next);
    }
  }

  return {};
}
} // namespace A_star
} // namespace path_finding
