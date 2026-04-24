#include <map_system.h>
#include <queue>
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
  constexpr node(point curr, point parent, float g, float h)
      : point(curr), parent(parent), g(g), h(h) {}

  inline double f() const { return g + h; }
  inline bool operator>(const node &other) const { return f() > other.f(); }
};

constexpr node default_node = {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX};

/**
 * @brief A_start寻路器
 */
class path_finder {
private:
  const i_path_context &ctx;
  /**
   * @open_list 存储待处理点 用优先队列 快速找到启发式函数最小的点
   * @close_list 标记已处理点 同时记录当前点的父节点 用于回溯路线
   */
  std::priority_queue<node, std::vector<node>, std::greater<node>> open_list;
  std::vector<std::vector<node>> closed_list;

  void init(point start, point end, bool dir_8);

public:
  path_finder(const i_path_context &ctx) : ctx(ctx) {
    closed_list.resize(
        ctx.get_height(),
        std::vector<node>(ctx.get_width(),
                          {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX}));
  }
  std::vector<point> find_path(point start, point end, bool dir_8);
};

/**
 * @brief A_star寻路算法
 * @return 起点到终点的路径. 若不能到终点, 返回{}
 */
std::vector<point> find_path(const i_path_context &ctx, point start, point end,
                             bool dir_8 = false);
} // namespace A_star

namespace JPS {
struct node : public point {
  point parent;
  float g, h;
  constexpr node(point curr, point parent, float g, float h)
      : point(curr), parent(parent), g(g), h(h) {}

  inline double f() const { return g + h; }
  inline bool operator>(const node &other) const { return f() > other.f(); }
};

constexpr node default_node = {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX};

/**
 * @brief JPS寻路器
 */
class path_finder {
private:
  const i_path_context &ctx;

  std::priority_queue<node, std::vector<node>, std::greater<node>> open_list;
  std::vector<std::vector<node>> closed_list;

  void init(point start, point end);
  point jump(point p, direction dir, point start, point end);
  bool has_forced_neighbor(point p, direction dir);

public:
  path_finder(const i_path_context &ctx) : ctx(ctx) {
    closed_list.resize(
        ctx.get_height(),
        std::vector<node>(ctx.get_width(),
                          {{-1, -1}, {-1, -1}, FLT_MAX, FLT_MAX}));
  }

  std::vector<point> find_path(point start, point end);
};

std::vector<point> find_path(const i_path_context &ctx, point start, point end);
} // namespace JPS

} // namespace path_finding
