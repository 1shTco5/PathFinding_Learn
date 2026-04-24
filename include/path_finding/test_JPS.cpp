#include "map_defines.h"
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

  node start_node = {
      start, {-1, -1}, e_dir::NONE, 0, manhattan_plus(start, end, true)};
  open_list.push(start_node);
  closed_list[start.y][start.x] = start_node;
}

search_directions path_finder::get_search_dirs(e_dir dir) {
  search_directions sd;

  if (dir == e_dir::NONE) {
    for (int i = 0; i < 8; i++)
      sd.dirs[sd.count++] = static_cast<e_dir>(i);
    return sd;
  }

  int d = static_cast<int>(dir);
  sd.dirs[sd.count++] = dir;

  if (d >= 4) { // 对角线运动
    // 剪枝规则: 除了正前方, 还要检查两个分量 (水平, 竖直)
    if (dir == e_dir::LEFT_UP) {
      sd.dirs[sd.count++] = e_dir::LEFT;
      sd.dirs[sd.count++] = e_dir::UP;
    } else if (dir == e_dir::LEFT_DOWN) {
      sd.dirs[sd.count++] = e_dir::LEFT;
      sd.dirs[sd.count++] = e_dir::DOWN;
    } else if (dir == e_dir::RIGHT_UP) {
      sd.dirs[sd.count++] = e_dir::RIGHT;
      sd.dirs[sd.count++] = e_dir::UP;
    } else {
      sd.dirs[sd.count++] = e_dir::RIGHT;
      sd.dirs[sd.count++] = e_dir::DOWN;
    }
  }
  // 直线运动
  return sd;
}

// NOTE!!!> 否则效率不如A*
// 1.不要用递归 大地图中深度爆炸 应该采用迭代
// 2.需要记忆化搜索 => 对跳点方向剪枝
point path_finder::jump(point curr, e_dir dir, point start, point end) {
  /* 迭代版本 */
  const auto &d = EDIR_TO_DIR[static_cast<int>(dir)];
  e_dir dir_horiz = direction(d.x, 0).to_enum();
  e_dir dir_vert = direction(0, d.y).to_enum();

  while (true) {
    curr.x += d.x;
    curr.y += d.y;

    if (!ctx.is_walkable(curr))
      return {-1, -1};
    if (curr == end)
      return curr;
    if (has_forced_neighbor(curr, dir))
      return curr;

    if (d.x != 0 && d.y != 0) {
      if (jump_linear(curr, dir_horiz, start, end))
        return curr;
      if (jump_linear(curr, dir_vert, start, end))
        return curr;
    }
  }

  /* 递归版本
  point next = {curr.x + d.x, curr.y +
  d.y};

  if (!ctx.is_walkable(next))
    return {-1, -1};
  if (next == end)
    return next;
  if (has_forced_neighbor(next, dir))
    return next;

  // 如果是对角线移动 在进行下一次对角线移动之前
  // 需要先递归检查水平和垂直方向
  if (d.x != 0 &&
  d.y != 0) { if (jump(next,
  {d.x, 0}, start, end) != point{-1, -1})
  return next; if (jump(next, {0, d.y}, start,
  end) != point{-1, -1}) return next;
  }
  return jump(next, dir, start, end);
  */
}

bool path_finder::jump_linear(point curr, e_dir dir, point start, point end) {
  const auto &d = EDIR_TO_DIR[static_cast<int>(dir)];

  while (true) {
    curr.x += d.x;
    curr.y += d.y;

    if (!ctx.is_walkable(curr))
      return false;
    if (curr == end)
      return true;
    if (has_forced_neighbor(curr, dir))
      return true;
  }
}

bool path_finder::has_forced_neighbor(point curr, e_dir dir) {
  const auto &d = EDIR_TO_DIR[static_cast<int>(dir)];

  // 1.直线探测
  if (d.x != 0 && d.y == 0) { // Horizontal
    if (!ctx.is_walkable({curr.x, curr.y + 1}) &&
        ctx.is_walkable({curr.x + d.x, curr.y + 1}))
      return true;
    if (!ctx.is_walkable({curr.x, curr.y - 1}) &&
        ctx.is_walkable({curr.x + d.x, curr.y - 1}))
      return true;
  } else if (d.x == 0 && d.y != 0) { // Vertical
    if (!ctx.is_walkable({curr.x + 1, curr.y}) &&
        ctx.is_walkable({curr.x + 1, curr.y + d.y}))
      return true;
    if (!ctx.is_walkable({curr.x - 1, curr.y}) &&
        ctx.is_walkable({curr.x - 1, curr.y + d.y}))
      return true;
  }
  // 2.对角线探测
  else if (d.x != 0 && d.y != 0) {
    if (!ctx.is_walkable({curr.x - d.x, curr.y}) &&
        ctx.is_walkable({curr.x - d.x, curr.y + d.y}))
      return true;
    if (!ctx.is_walkable({curr.x, curr.y - d.y}) &&
        ctx.is_walkable({curr.x + d.x, curr.y - d.y}))
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

    search_directions sd = get_search_dirs(curr.dir);
    for (int i = 0; i < sd.count; i++) {
      point jump_point = jump(curr, sd.dirs[i], start, end);

      if (jump_point != point{-1, -1}) {
        float new_g = curr.g + manhattan_plus(curr, jump_point, true);
        if (closed_list[jump_point.y][jump_point.x].g <= new_g)
          continue;
        node next = {jump_point, curr, sd.dirs[i], new_g,
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
