#pragma once

#include "random.h"

#include <cassert>

#define ASSERT_THROW(expr, exception) \
do {                                  \
    try {                             \
        expr;                         \
        assert(!"no exception");      \
    } catch (const exception&) {      \
    } catch (...) {                   \
        assert(!"other exception");   \
    }                                 \
} while (false)

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace nuclear {

////////////////////////////////////////////////////////////////////////////////////////////////////

extern void RunTests();

////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace nuclear
