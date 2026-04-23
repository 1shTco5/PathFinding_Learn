#include <map_system.h>
#include <path_finding.h>
#include <utils.h>

using namespace std;
using namespace utils;
using namespace map_system;
using namespace path_finding;

int main() {
  grid_map gmap = get_grid_map();
  // gmap.print();
  {
    time::timer timer("A star");
    gmap.A_star_4_dir();
  }
  // gmap.print(true);
}
