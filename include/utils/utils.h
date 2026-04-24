#include <chrono>
#include <iostream>
#include <map_system.h>
#include <string>

using namespace map_system;

namespace utils {
namespace distance {
float manhattan_plus(point s, point e, bool dir_8 = false);
};

namespace time {
/**
 * @brief 基于RAII编程范式的计时器
 * @details 进入作用域构造计时器开始计时 离开作用域析构计时器打印时间
 */
class timer {
private:
  std::string name;
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

public:
  timer(const std::string &name);
  ~timer();
};
}; // namespace time
} // namespace utils
