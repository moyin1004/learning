INC_DIR:= ./
SRC_DIR:= ./
SRCS:=$(wildcard *.cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))

LIBS:= -lpthread -llog4cpp

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) 

EXE:=./server.out

$(EXE):$(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm $(EXE) $(OBJS)
