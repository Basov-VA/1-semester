#include "nuclear.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <set>

using ::nuclear::random::Population;
using ::nuclear::random::Random;
using ::nuclear::random::Range;

void TestSimple() {
    ::nuclear::random::RandomGenerator gen(5);

    assert(gen.Generate<int>(-1, 1) == 1);
    assert(std::abs(gen.Generate<double>() - 0.0384946) < 1e-4);
    assert(gen.Generate<bool>() == false);
    assert(gen.Generate<long long>() == -5977996037847506718LL);
    assert(gen.Generate<char>() == 't');
    assert(gen.GenerateSeq<short>(5) == (std::vector<short>{-31535, -16189, 15977, -4552, -19860}));
    assert(gen.Generate<std::string>(10, 'a', 'e') == "cbbacecdcc");
    assert(gen.Generate<std::string>(Range{5, 10}, 'a', 'e') == "bcdcaddc");
    assert(gen.Generate<int>(Population<int>({1, -1, 100, -100})) == 1);
    assert(gen.Generate<std::string>(5, Population<char>({'a', '_', 'Y', '0', '-'})) == "_a_a0");
    assert(gen.Generate<std::set<std::string>>(7, Range{3, 5}, Population{'0', '7'}) ==
            (std::set<std::string>{"06375", "23010", "2574", "4472", "5321", "5772", "75405"}));
    assert(gen.Generate<int>(Population<int>({1, -1, 100, -100})) == 100);
}

void TestGlobal() {
    assert(Random<int>() != Random<int>());
    assert(Random<std::string>(2, 'a', 'o') != Random<std::string>(2, Population('a', 'o')));
    assert(Random<std::list<std::string>>(10, 5, 'C', 'X') != Random<std::list<std::string>>(10, 5, 'C', 'X'));
}

void ::nuclear::RunTests() {
    TestSimple();
    TestGlobal();
}
