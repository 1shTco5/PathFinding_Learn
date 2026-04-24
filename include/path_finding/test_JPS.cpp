#include "map_system.h"
#include <cfloat>
#include <path_finding.h>
#include <utils.h>
#include <vector>

using namespace utils::distance;

namespace path_finding {
namespace JPS {

void path_finder::init(point start, point end) {
  open_list = {};
  for (int i = 0; i < ctx.get_height(); i++) {
    closed_list[i].assign(ctx.get_width(), default_node);
  }

  node start_node = {start, {-1, -1}, 0, manhattan_plus(start, end, true)};
  open_list.push(start_node);
  closed_list[start.y][start.x] = start_node;
}

// NOTE!!!> 否则效率不如A*
// 1.不要用递归 大地图中深度爆炸 应该采用迭代
// 2.需要记忆化搜索
point path_finder::jump(point p, direction dir, point start, point end) {
  point next = {p.x + dir.x, p.y + dir.y};

  if (!ctx.is_walkable(next))
    return {-1, -1};
  if (next == end)
    return next;
  if (has_forced_neighbor(next, dir))
    return next;

  // 如果是对角线移动 在进行下一次对角线移动之前
  // 需要先递归检查水平和垂直方向
  if (dir.x != 0 && dir.y != 0) {
    if (jump(next, {dir.x, 0}, start, end) != point{-1, -1})
      return next;
    if (jump(next, {0, dir.y}, start, end) != point{-1, -1})
      return next;
  }
  return jump(next, dir, start, end);
}

bool path_finder::has_forced_neighbor(point p, direction dir) {
  // 1.直线探测
  if (dir.x != 0 && dir.y == 0) { // Horizontal
    if (!ctx.is_walkable({p.x, p.y + 1}) &&
        ctx.is_walkable({p.x + dir.x, p.y + 1}))
      return true;
    if (!ctx.is_walkable({p.x, p.y - 1}) &&
        ctx.is_walkable({p.x + dir.x, p.y - 1}))
      return true;
  } else if (dir.x == 0 && dir.y != 0) { // Vertical
    if (!ctx.is_walkable({p.x + 1, p.y}) &&
        ctx.is_walkable({p.x + 1, p.y + dir.y}))
      return true;
    if (!ctx.is_walkable({p.x - 1, p.y}) &&
        ctx.is_walkable({p.x - 1, p.y + dir.y}))
      return true;
  }
  // 2.对角线探测
  else if (dir.x != 0 && dir.y != 0) {
    if (!ctx.is_walkable({p.x - dir.x, p.y}) &&
        ctx.is_walkable({p.x - dir.x, p.y + dir.y}))
      return true;
    if (!ctx.is_walkable({p.x, p.y - dir.y}) &&
        ctx.is_walkable({p.x + dir.x, p.y - dir.y}))
      return true;
  }
  return false;
}

std::vector<point> path_finder::find_path(point start, point end) {
  init(start, end);

  while (!open_list.empty()) {
    node curr = open_list.top();
    open_list.pop();

    if (curr == end)
      break;
    if (curr.g > closed_list[curr.y][curr.x].g)
      continue;

    for (int i = 0; i < 8; i++) {
      point jump_point = jump(curr, DIR[i], start, end);

      if (jump_point != point{-1, -1}) {
        float new_g = curr.g + manhattan_plus(curr, jump_point, true);
        if (closed_list[jump_point.y][jump_point.x].g <= new_g)
          continue;
        node next = {jump_point, curr, new_g,
                     manhattan_plus(jump_point, end, true)};
        open_list.push(next);
        closed_list[jump_point.y][jump_point.x] = next;
      }
    }
  }

  if (closed_list[end.y][end.x].g == FLT_MAX)
    return {};
  std::vector<point> path;
  node curr = closed_list[end.y][end.x];
  while (true) {
    path.push_back(curr);
    if (curr.parent.x == -1 && curr.parent.y == -1)
      break;
    curr = closed_list[curr.parent.y][curr.parent.x];
  }
  std::reverse(path.begin(), path.end());

  return path;
}

std::vector<point> find_path(const i_path_context &ctx, point start,
                             point end) {
  return path_finder(ctx).find_path(start, end);
}
} // namespace JPS
} // namespace path_finding
