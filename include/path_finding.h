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
  float g, h;
  node(point curr, point parent, float g, float h)
      : point(curr), parent(parent), g(g), h(h) {}

  double f() const { return g + h; }

  bool operator>(const node &other) const { return f() > other.f(); }
};

/**
 * @breif 方向
 * @property dist_scale 直线方向倍数为 1 斜线方向倍数为 1.414
 */
struct direction : public point {
  float dist_scale;

  direction(point dir, float scale) : point(dir), dist_scale(scale) {}
};

/**
 * @brief A_star寻路算法
 * @return 起点到终点的路径. 若不能到终点, 返回{}
 */
std::vector<point> A_star(grid_map &gmap, bool dir_8 = false);
} // namespace path_finding
