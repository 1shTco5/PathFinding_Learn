#include <algorithm>
#include <iostream>
#include <map_system.h>
#include <path_finding.h>
#include <random>
#include <vector>

namespace map_system {
grid_map get_grid_map() {
  std::cout << "Input a random seed: \n";
  unsigned int seed;
  std::cin >> seed;

  std::cout << "Input (width, height): \n";
  int width, height;
  std::cin >> width >> height;

  grid_map_generator generator(width, height, seed);
  grid_map gmap = generator.generate();
  return gmap;
}

void grid_map::A_star(bool dir_8) { path = path_finding::A_star::A_star(*this, dir_8); }

void grid_map::print(bool print_path) {
  std::cout << "Start: (" << start.x << ',' << start.y << ")\n";
  std::cout << "End  : (" << end.x << ',' << end.y << ")\n";

  for (int y = 0; y < grid.size(); y++) {
    for (int x = 0; x < grid[0].size(); x++) {
      if (start.x == x && start.y == y) {
        std::cout << "S ";
      } else if (end.x == x && end.y == y) {
        std::cout << "E ";
      } else if (print_path && !path.empty() &&
                 std::find_if(path.begin(), path.end(), [&](const point &p) {
                   return p.x == x && p.y == y;
                 }) != path.end()) {
        std::cout << "* ";
      }

      else {
        std::cout << grid[y][x] << ' ';
      }
    }
    std::cout << '\n';
  }
  if (print_path) {
    if (path.empty()) {
      std::cout << "Path not found!" << std::endl;
    } else {
      std::cout << "Path length: " << path.size() << std::endl;
    }
  }
}

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
