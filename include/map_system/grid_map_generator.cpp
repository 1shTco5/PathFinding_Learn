#include <map_system.h>

namespace map_system {
point grid_map_generator::get_random_point() {
  std::uniform_int_distribution<int> distX(0, width - 1);
  std::uniform_int_distribution<int> distY(0, height - 1);
  return {distX(rng), distY(rng)};
}

grid_map grid_map_generator::generate(float obstacle_density) {
  grid_map gmap(width, height);
  std::vector<std::vector<int>> &grid = gmap.grid;

  // 随机填充障碍物
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (dist(rng) < obstacle_density) {
        grid[i][j] = 0;
      }
    }
  }

  // 随机生成起点和终点
  gmap.start = get_random_point();
  gmap.end = get_random_point();
  grid[gmap.start.y][gmap.start.x] = 1;
  grid[gmap.end.y][gmap.end.x] = 1;

  return gmap;
}
} // namespace map_system
