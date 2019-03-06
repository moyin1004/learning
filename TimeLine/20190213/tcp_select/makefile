CC:= g++
INC_DIR:= ./include/
SRC_DIR:= ./

SRCS:= $(wildcard $(SRC_DIR)*.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
CXXFLAGS:= -g $(addprefix -I, $(INC_DIR))

LIBS:= -lpthread 

%.o:%.cc
	$(CC) -o $@ -c $< $(CXXFLAGS)

BIN1:= server.out
BIN2:= client.out
OBIN1:= tcp_server.o
OBIN2:= tcp_client.o
BIN:= $(BIN1) $(BIN2)

all:$(BIN)

$(BIN1):$(OBIN1) Server.o
	$(CC) -o $@ $^

$(BIN2):$(OBIN2)
	$(CC) -o $@ $^

run:
	./test.out

print:
	@echo $(OBJS)
	@echo $(BIN1)
	@echo $(BIN2)

clean:
	rm $(OBJS) $(BIN)
