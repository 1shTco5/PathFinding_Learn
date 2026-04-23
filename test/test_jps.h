#include <map_system.h>

using namespace map_system;

namespace test_jps {
  class test_grid_map : public grid_map {
  private:
    std::vector<point> jump_points;

  public:
    void get_jump_point();
  };
}
