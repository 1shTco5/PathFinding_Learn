#include <map_system.h>
#include <vector>

using namespace map_system;

namespace path_finding {
/**
 * @brief 定义节点
 * @property (x,y) 坐标
 * @property g 已走距离
 * @property h 预估到终点距离
 */
struct node : public point {
  point parent;
  int g, h;
  node(point curr, point parent, int g, int h) : point(curr), parent(parent), g(g), h(h) {}

  long long f() const { return g + h; }

  bool operator>(const node &other) const { return f() > other.f(); }
};

/**
 * @brief A_star寻路算法
 * @return 起点到终点的路径. 若不能到终点, 返回{}
 */
std::vector<point> A_star_4_dir(grid_map &gmap);
std::vector<point> A_star_8_dir(grid_map &gmap);
} // namespace path_finding
