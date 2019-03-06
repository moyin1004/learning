CC:= g++
INC_DIR:= ./include/
SRC_DIR:= ./src/
TEST_DIR:= ./
SRCS:= $(wildcard $(SRC_DIR)*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
TESTS:= $(wildcard $(TEST_DIR)*.cc)
CXXFLAGS:= -g $(addprefix -I, $(INC_DIR))

LIBS:= -lpthread

BIN:= $(patsubst %.cc, %.out, $(TESTS))

%.o:%.cc
	$(CC) -o $@ -c $< $(CXXFLAGS)

all: $(BIN)

BIN1:= tcp_server.out
BIN2:= tcp_client.out
OBIN1:= tcp_server.o
OBIN2:= tcp_client.o

$(BIN1):$(OBJS) $(OBIN1)
	$(CC) -o $@ $^ $(LIBS)

$(BIN2):$(OBIN2)
	$(CC) -o $@ $^

run:
	./test.out

print:
	@echo $(OBJS)
	@echo $(BIN)

clean:
	rm $(OBJS) $(BIN) $(OBIN1) $(OBIN2)
