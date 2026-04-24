#include <iostream>
#include <map_system.h>

namespace map_system {
grid_map get_grid_map() {
  std::cout << "Input a random seed: \n";
  unsigned int seed;
  std::cin >> seed;

  std::cout << "Input (width, height): \n";
  int width, height;
  std::cin >> width >> height;

  std::cout << "Input obstacle density: \n";
  float obstacle_density;
  std::cin >> obstacle_density;

  grid_map_generator generator(width, height, seed);
  grid_map gmap = generator.generate(obstacle_density);
  return gmap;
}
} // namespace map_system
