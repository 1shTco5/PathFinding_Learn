#include <cstdlib>
#include <utils.h>

namespace utils {
namespace distance {
int manhattan(point s, point e) { return abs(s.x - e.x) + abs(s.y - e.y); }
} // namespace distance
} // namespace utils
