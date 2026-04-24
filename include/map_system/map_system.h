#pragma once
#include <random>
#include <utility>
#include <vector>

namespace map_system {

inline constexpr float SQRT2 = 1.4142f;

/**
 * @brief 网格点 (x,y)
 */
struct point {
  int x, y;

  constexpr point(int x, int y) : x(x), y(y) {}

  bool operator==(const point &other) { return x == other.x && y == other.y; }
  bool operator!=(const point &other) { return !(*this == other); }
};

/**
 * @breif 方向
 * @property dist_scale 直线方向倍数为 1 斜线方向倍数为 1.414
 */
struct direction : public point {
  float dist_scale;

  constexpr direction(point dir, float scale = 1)
      : point(dir), dist_scale(scale) {}
  constexpr direction(int x, int y, float scale = 1)
      : point{x, y}, dist_scale(scale) {}
};

constexpr direction DIR[8] = {
    {{0, -1}, 1},      {{0, 1}, 1},      {{-1, 0}, 1},     {{1, 0}, 1},
    {{-1, -1}, SQRT2}, {{-1, 1}, SQRT2}, {{1, -1}, SQRT2}, {{1, 1}, SQRT2}};

/**
 * @brief 用于寻路算法的只读接口
 */
class i_path_context {
public:
  virtual ~i_path_context() = default;
  virtual bool is_walkable(point p) const = 0;
  virtual float get_cost(point p) const = 0;
  virtual int get_width() const = 0;
  virtual int get_height() const = 0;
};

/**
 * @brief 存储网格数据的核心数据结构
 * @property grid 二维 vector 存储地图格点信息
 * @property start 起点
 * @property end 终点
 */
class grid_map : public i_path_context {
public:
  std::vector<std::vector<int>> grid;
  int width, height;       ///< 宽高
  point start;             ///< 起点坐标
  point end;               ///< 终点坐标
  std::vector<point> path; ///< 路径

  grid_map(int width, int height)
      : grid(height, std::vector<int>(width, 1)), width(width), height(height),
        start{0, 0}, end{0, 0} {}

  /* 实现 i_path_context 接口 */
  bool is_walkable(point p) const override;
  float get_cost(point p) const override;
  int get_width() const override;
  int get_height() const override;

  void print(bool print_path = false);
};

/**
 * @brief 网格地图生成器
 */
class grid_map_generator {
private:
  int width, height;
  std::mt19937 rng;

  point get_random_point();

public:
  /**
   * @param width 网格地图宽
   * @param height 网格地图高
   * @param seed 生成器种子 默认为0
   */
  grid_map_generator(int width, int height, unsigned int seed)
      : width(width), height(height), rng(seed) {}
  /**
   * @brief 网格地图生成函数
   * @param obstacle_density 障碍物密度 默认为0.3
   */
  grid_map generate(float obstacle_density = 0.3f);
};

grid_map get_grid_map();
} // namespace map_system
