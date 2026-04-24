#include <algorithm>
#include <cstdlib>
#include <utils.h>

namespace utils {
namespace distance {
float manhattan_plus(point s, point e, bool dir_8) {
  if (dir_8) {
    float dx = static_cast<float>(abs(s.x - e.x));
    float dy = static_cast<float>(abs(s.y - e.y));
    return (dx + dy) + (1.414f - 2.0f) * std::min(dx, dy);
  }
  return static_cast<float>(abs(s.x - e.x) + abs(s.y - e.y));
}
} // namespace distance
} // namespace utils
