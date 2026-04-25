#pragma once

#include <cstddef>
#include <functional>
namespace map_system {
inline constexpr float SQRT2 = 1.4142f;

/**
 * @brief 方向枚举
 */
enum class e_dir : int {
  UP = 0,
  DOWN,
  LEFT,
  RIGHT,
  LEFT_UP,
  LEFT_DOWN,
  RIGHT_UP,
  RIGHT_DOWN,
  NONE
};

static constexpr e_dir DIR_TO_EDIR[3][3] = {
    // y=-1        y=0           y=1
    {e_dir::LEFT_UP, e_dir::LEFT, e_dir::LEFT_DOWN},   // x = -1
    {e_dir::UP, e_dir::NONE, e_dir::DOWN},             // x =  0
    {e_dir::RIGHT_UP, e_dir::RIGHT, e_dir::RIGHT_DOWN} // x =  1
};

/**
 * @brief 网格点 (x,y)
 */
struct point {
  int x, y;

  constexpr point(int x, int y) : x(x), y(y) {}

  bool operator==(const point &other) const { return x == other.x && y == other.y; }
  bool operator!=(const point &other) const { return !(*this == other); }
};

struct point_hash {
  size_t operator()(const point &p) const {
    return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
  }
};

/**
 * @brief 方向
 * @property dist_scale 直线方向倍数为 1 斜线方向倍数为 1.414
 */
struct direction : public point {
  float dist_scale;

  constexpr direction(point dir, float scale = 1)
      : point(dir), dist_scale(scale) {}
  constexpr direction(int x, int y, float scale = 1)
      : point{x, y}, dist_scale(scale) {}

  e_dir to_enum() const { return DIR_TO_EDIR[x + 1][y + 1]; }
};

constexpr direction EDIR_TO_DIR[9] = {
    {0, -1, 1.0f},   // UP
    {0, 1, 1.0f},    // DOWN
    {-1, 0, 1.0f},   // LEFT
    {1, 0, 1.0f},    // RIGHT
    {-1, -1, SQRT2}, // LEFT_UP
    {-1, 1, SQRT2},  // LEFT_DOWN
    {1, -1, SQRT2},  // RIGHT_UP
    {1, 1, SQRT2},   // RIGHT_DOWN
    {0, 0, 0}        // NONE
};
} // namespace map_system
