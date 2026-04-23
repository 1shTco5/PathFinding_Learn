#pragma once
#include <random>
#include <utility>
#include <vector>

namespace map_system {
/**
 * @brief 网格点 (x,y)
 */
struct point {
  int x, y;
};

/**
 * @brief 存储网格数据的核心数据结构
 * @property grid 二维 vector 存储地图格点信息
 * @property start 起点
 * @property end 终点
 */
class grid_map {
public:
  /**
   * @brief 地图格点数据
   * @details 0 代表障碍物. 其他代表当前格的cost
   */
  std::vector<std::vector<int>> grid;
  int width, height; ///< 宽高
  point start;       ///< 起点坐标
  point end;         ///< 终点坐标
  std::vector<point> path; ///< 路径

  grid_map(int width, int height)
      : grid(height, std::vector<int>(width, 1)), width(width), height(height),
        start{0, 0}, end{0, 0} {}

  /**
   * @brief A_star寻路
   */
  void A_star(bool dir_8 = false);

  /**
   * @brief 打印网格地图
   */
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
  grid_map_generator(int width, int height, unsigned int seed = 0)
      : width(width), height(height), rng(seed) {}
  /**
   * @brief 网格地图生成函数
   * @param obstacle_density 障碍物密度 默认为0.3
   */
  grid_map generate(float obstacle_density = 0.3f);
};

/**
 * @brief 获取一个网格地图
 */
grid_map get_grid_map();
} // namespace map_system
