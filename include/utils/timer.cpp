#include <utils.h>

namespace utils {
namespace time {
timer::timer(const std::string &name)
    : name(name), start_time(std::chrono::high_resolution_clock::now()) {}
timer::~timer() {
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);

  std::cout << "Timer [" << name << "] took:" << duration.count() << " ms"
            << std::endl;
}
} // namespace time
} // namespace utils
