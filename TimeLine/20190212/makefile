CC:= g++
INC_DIR:= ./
SRC_DIR:= ./
TEST_DIR:= ./

SRCS:= $(wildcard $(SRC_DIR)*.cc)
TESTS:= $(wildcard $(TEST_DIR)*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
OTEST:= $(patsubst %.cc, %.o, $(TESTS))

CXXFLAGS:= -g $(addprefix -I, $(INC_DIR))

LIBS:= -lpthread

BINS:= $(patsubst %.cc, %.out, $(TESTS))

all:$(BINS) $(OTEST)

%.o:%.cc
	$(CC) -o $@ -c $<

%.out:%.o
	$(CC) -o $@ $<

print:
	@echo $(OBJS)
	@echo $(BINS)

clean:
	rm $(OBJS) $(BINS)
