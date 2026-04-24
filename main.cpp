#include <map_system.h>
#include <path_finding.h>
#include <utils.h>

using namespace std;
using namespace utils;
using namespace map_system;
using namespace path_finding;

int main() {
  grid_map gmap = get_grid_map();
  gmap.print();
  {
    time::timer timer("A star[4 dir]");
    gmap.path = A_star::A_star(gmap);
  }
  gmap.print(true);
  {
    time::timer timer("A star[8 dir]");
    gmap.path = A_star::A_star(gmap, true);
  }
  gmap.print(true);
  {

  }
}
