#include <map_system.h>
#include <vector>

using namespace map_system;

namespace path_finding {
namespace A_star {
/**
 * @brief 定义节点
 * @property (x,y) 坐标
 * @property g 已走距离
 * @property h 预估到终点距离
 */
struct node : public point {
  point parent;
  float g, h;
  node(point curr, point parent, float g, float h)
      : point(curr), parent(parent), g(g), h(h) {}

  inline double f() const { return g + h; }
  inline bool operator>(const node &other) const { return f() > other.f(); }
};

/**
 * @brief A_star寻路算法
 * @return 起点到终点的路径. 若不能到终点, 返回{}
 */
std::vector<point> A_star(grid_map &gmap, bool dir_8 = false);
} // namespace A_star

namespace JPS {}

} // namespace path_finding
