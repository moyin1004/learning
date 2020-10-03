INC_DIR:= ./
SRC_DIR:= ./
LIB_DIR:= ./

SRCS:= $(wildcard $(SRC_DIR)*.cpp)
OBJS:= $(patsubst %.cpp, %.o, $(SRCS))

CXX:= g++
CXXFLAGS:= -c -g -std=c++17 $(addprefix -I, $(INC_DIR))

EXE:= ./test.out

%.o:%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

$(EXE):$(OBJS)
	$(CXX) -o $@ $^

run:
	$(EXE)

print:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(EXE)

clean:
	rm $(OBJS)
	rm $(EXE)
