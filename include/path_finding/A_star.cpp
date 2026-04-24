#include <algorithm>
#include <cfloat>
#include <map_system.h>
#include <path_finding.h>
#include <queue>
#include <utils.h>
#include <vector>

using namespace map_system;
using namespace utils::distance;

namespace path_finding {
namespace A_star {

std::vector<point> find_path(const i_path_context &context, point start,
                             point end, bool dir_8) {
  return path_finder(context).find_path(start, end, dir_8);
}

void path_finder::init(point start, point end, bool dir_8) {
  open_list = {};
  closed_list.resize(ctx.get_height(),
                     std::vector<node>(ctx.get_width(),
                                       {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX}));

  node start_node = {start, {-1, -1}, 0, manhattan_plus(start, end, dir_8)};
  open_list.push(start_node);
  closed_list[start.y][start.x] = start_node;
}

std::vector<point> path_finder::find_path(point start, point end, bool dir_8) {
  init(start, end, dir_8);

  while (!open_list.empty()) {
    node curr = open_list.top();
    open_list.pop();

    if (curr.x == end.x && curr.y == end.y)
      break;
    if (curr.g > closed_list[curr.y][curr.x].g)
      continue;

    int dir_count = dir_8 ? 8 : 4;
    for (int i = 0; i < dir_count; i++) {
      int nx = curr.x + DIR[i].x;
      int ny = curr.y + DIR[i].y;

      if (ctx.is_walkable({nx, ny})) {
        if (closed_list[ny][nx].g <=
            curr.g + ctx.get_cost({nx, ny}) * DIR[i].dist_scale)
          continue;

        node next = {{nx, ny},
                     curr,
                     curr.g + ctx.get_cost({nx, ny}) * DIR[i].dist_scale,
                     manhattan_plus({nx, ny}, end, dir_8)};
        open_list.push(next);
        closed_list[ny][nx] = next;
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
} // namespace A_star
} // namespace path_finding
