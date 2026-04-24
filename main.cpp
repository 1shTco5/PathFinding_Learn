#include <map_system.h>
#include <path_finding.h>
#include <utils.h>

using namespace std;
using namespace utils;
using namespace map_system;
using namespace path_finding;

int main(int argc, char *argv[]) {
  bool should_print = (argc > 1 && std::string(argv[1]) == "1");

  grid_map gmap = get_grid_map();
  if (should_print) {
    cout << "--- Initial Map ---" << endl;
    gmap.print();
  }
  // {
  //   time::timer timer("--- A star[4 dir] ---");
  //   gmap.path = A_star::find_path(gmap, gmap.start, gmap.end);
  // }
  // if (should_print)
  //   gmap.print(true);
  {
    time::timer timer("--- A star[8 dir] ---");
    gmap.path = A_star::find_path(gmap, gmap.start, gmap.end, true);
  }
  if (should_print)
    gmap.print(true);
  {
    time::timer timer("--- JPS ---");
    gmap.path = JPS::find_path(gmap, gmap.start, gmap.end);
  }
  if (should_print)
    gmap.print(true);
}
