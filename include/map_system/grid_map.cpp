#include <map_system.h>
#include <iostream>

namespace map_system {
bool grid_map::is_walkable(point p) const {
  if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
    return false;
  return grid[p.y][p.x] != 0;
}
float grid_map::get_cost(point p, bool is_diag) const {
  if (is_walkable(p)) {
    float cost_scale = is_diag ? SQRT2 : 1;
    return static_cast<float>(grid[p.y][p.x]) * cost_scale;
  }
  return FLT_MAX;
}
int grid_map::get_width() const { return width; }
int grid_map::get_height() const { return height; }

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

} // namespace map_system
