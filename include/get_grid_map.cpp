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

  grid_map_generator generator(width, height, seed);
  grid_map gmap = generator.generate();
  return gmap;
}
} // namespace map_system
