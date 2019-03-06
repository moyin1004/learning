CC:= g++
INC_DIR:= ./include/
SRC_DIR:= ./src/
TEST_DIR:= ./

SRCS:= $(wildcard $(SRC_DIR)*.cc $(TEST_DIR)*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
CXXFLAGS:= -g $(addprefix -I, $(INC_DIR))

LIBS:= -lpthead

BIN:= ./bin/test.out

%.o:%.cc
	$(CC) -o $@ -c $< $(CXXFLAGS)

$(BIN):$(OBJS)
	$(CC) -o $@ $^

run:
	./bin/test.out

print:
	@echo $(OBJS)
	@echo $(SRCS)

clean:
	rm $(OBJS) $(BIN)
