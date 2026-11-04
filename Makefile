CC = gcc
CXX = g++
CFLAGS = -std=c99 -O2 -Wall -Wextra -Wpedantic -Werror
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -Wpedantic -Werror
C_SOURCES := $(wildcard src/c/*.c)
CPP_SOURCES := $(wildcard src/cpp/*.cpp)
C_BINS := $(patsubst src/c/%.c,build/c/%,$(C_SOURCES))
CPP_BINS := $(patsubst src/cpp/%.cpp,build/cpp/%,$(CPP_SOURCES))
.PHONY: all test sanitize clean stats pdf
all: $(C_BINS) $(CPP_BINS)
build/c/%: src/c/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -lm -o $@
build/cpp/%: src/cpp/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@
test: all
	python3 tests/run.py
	python3 tests/labs.py
sanitize:
	python3 tools/sanitize.py
stats:
	python3 tools/analyze_sources.py
clean:
	rm -rf build

pdf:
	python3 tools/build_pdf.py
