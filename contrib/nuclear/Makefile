SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
UNITTESTS := ut/*.cpp
TESTS := tests
NUCLEAR_LIB := libnuclear.a

CXXFLAGS := -O2 -std=c++20 -Wall -Werror

all: compile

compile: $(SOURCES) $(OBJECTS)
	ar cr $(NUCLEAR_LIB) $(OBJECTS)

.cpp.o: $(wildcard *.h)
	g++ -c $(CXXFLAGS) $< -o $@

ut/%.cpp: compile
	g++ $(CXXFLAGS) -l$(NUCLEAR_LIB) $@ -I ./ -o $(TESTS)
	./$(TESTS)

test: $(UNITTESTS)

clean:
	rm -f $(OBJECTS) $(NUCLEAR_LIB) $(TESTS)
