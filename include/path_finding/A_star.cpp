#include <algorithm>
#include <cfloat>
#include <climits>
#include <functional>
#include <map_system.h>
#include <path_finding.h>
#include <queue>
#include <utils.h>
#include <vector>

using namespace map_system;
using namespace utils::distance;

namespace path_finding {
namespace A_star {
std::vector<point> A_star(grid_map &gmap, bool dir_8) {
  std::vector<std::vector<int>> &grid = gmap.grid;
  int width = gmap.width;
  int height = gmap.height;
  point start = gmap.start;
  point end = gmap.end;

  /**
   * @open_list 存储待处理点 用优先队列 快速找到启发式函数最小的点
   * @close_list 标记已处理点 同时记录当前点的父节点 用于回溯路线
   */
  std::priority_queue<node, std::vector<node>, std::greater<node>> open_list;
  std::vector<std::vector<node>> close_list(
      height, std::vector<node>(width, {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX}));

  node start_node = {start, {-1, -1}, 0, manhattan_plus(start, end, dir_8)};
  open_list.push(start_node);
  close_list[start.y][start.x] = start_node;
  while (!open_list.empty()) {
    node curr = open_list.top();
    open_list.pop();

    if (curr.x == end.x && curr.y == end.y)
      break;
    if (curr.g > close_list[curr.y][curr.x].g)
      continue;

    int dir_count = dir_8 ? 8 : 4;
    for (int i = 0; i < dir_count; i++) {
      int nx = curr.x + DIR[i].x;
      int ny = curr.y + DIR[i].y;

      if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
          grid[ny][nx] != 0) {
        if (close_list[ny][nx].g <= curr.g + grid[ny][nx] * DIR[i].dist_scale)
          continue;

        node next = {{nx, ny},
                     curr,
                     curr.g + grid[ny][nx] * DIR[i].dist_scale,
                     manhattan_plus({nx, ny}, end, dir_8)};
        open_list.push(next);
        close_list[ny][nx] = next;
      }
    }
  }

  if (close_list[end.y][end.x].g == INT_MAX)
    return {};

  std::vector<point> path;
  node curr = close_list[end.y][end.x];
  while (true) {
    path.push_back(curr);
    if (curr.parent.x == -1 && curr.parent.y == -1)
      break;
    curr = close_list[curr.parent.y][curr.parent.x];
  }
  std::reverse(path.begin(), path.end());

  return path;
}
} // namespace A_star
} // namespace path_finding
