#include "random.h"

#include <memory>

namespace nuclear::random {

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace details {

RandomGenerator* GlobalGenerator() {
    static thread_local RandomGenerator global_generator;
    return std::addressof(global_generator);
}

}  // namespace nuclear::random::details

////////////////////////////////////////////////////////////////////////////////////////////////////

RandomGenerator::RandomGenerator()
    : RandomGenerator(std::random_device{}())
{ }

RandomGenerator::RandomGenerator(uint64_t seed)
    : generator_(seed)
{ }

////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace nuclear::random
