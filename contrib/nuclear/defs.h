#pragma once

#define DEFINED_LIB(x) (defined(_GLIBCXX_##x) || defined(_LIBCPP_##x))
#define DEFINED_LIBS_2(x, y) DEFINED_LIB(x) || DEFINED_LIB(y)
#define DEFINED_LIBS_3(x, ...) DEFINED_LIB(x) || DEFINED_LIBS_2(__VA_ARGS__)
#define DEFINED_LIBS_4(x, ...) DEFINED_LIB(x) || DEFINED_LIBS_3(__VA_ARGS__)
#define DEFINED_LIBS_5(x, ...) DEFINED_LIB(x) || DEFINED_LIBS_4(__VA_ARGS__)
#define DEFINED_LIBS_6(x, ...) DEFINED_LIB(x) || DEFINED_LIBS_5(__VA_ARGS__)
#define DEFINED_LIBS_7(x, ...) DEFINED_LIB(x) || DEFINED_LIBS_6(__VA_ARGS__)
