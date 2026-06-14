CXX      := g++
CXXFLAGS := -std=c++17 -O2 -pthread -Wall -Wextra -g

SRCS     := $(filter-out lambda.cc, $(wildcard *.cc))
EXES     := $(SRCS:%.cc=%)

.PHONY: all run clean tsan

all: $(EXES)

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

run: all
	@for e in $(EXES); do echo "=== $$e ==="; ./$$e; done

clean:
	rm -f $(EXES)

tsan: CXXFLAGS += -fsanitize=thread
tsan: clean all
