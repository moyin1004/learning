CXX := g++
CXXFLAGS := -std=c++23 -fmodules-ts -O2
GCC_VERSION := $(shell $(CXX) -dumpversion)
STD_CC := /usr/include/c++/$(GCC_VERSION)/bits/std.cc

.PHONY: all clean run

all: modules_test

std_module.o: $(STD_CC)
	$(CXX) $(CXXFLAGS) -c -x c++ $< -o $@

modules_test.o: modules_test.cppm std_module.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

modules_test: modules_test.o std_module.o
	$(CXX) $(CXXFLAGS) -o $@ $^

run: modules_test
	./modules_test

clean:
	rm -f modules_test modules_test.o std_module.o
	rm -rf gcm.cache/
