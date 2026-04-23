#include <algorithm>
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
point dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

std::vector<point> A_star_4_dir(grid_map &gmap) {
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
      height, std::vector<node>(width, {{-1, -1}, {-1, -1}, INT_MAX, INT_MAX}));

  node start_node = {start, {-1, -1}, 0, manhattan(start, end)};
  open_list.push(start_node);
  close_list[start.y][start.x] = start_node;
  while (!open_list.empty()) {
    node curr = open_list.top();
    open_list.pop();

    if (curr.x == end.x && curr.y == end.y)
      break;
    if (curr.g > close_list[curr.y][curr.x].g)
      continue;

    for (int i = 0; i < 4; i++) {
      int nx = curr.x + dir[i].x;
      int ny = curr.y + dir[i].y;

      if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
          grid[ny][nx] != 0) {
        if (close_list[ny][nx].g <= curr.g + grid[ny][nx])
          continue;

        node next = {
            {nx, ny}, curr, curr.g + grid[ny][nx], manhattan({nx, ny}, end)};
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
} // namespace path_finding
