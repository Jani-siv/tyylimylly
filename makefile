CXXFLAGS = -Wall -g
INCLUDES = -I ./include/
SRC_DIR = ./src/
SRCS = $(SRC_DIR)main.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = tyylimylly
OUT_DIR = ./out
.PHONY: depend clean

all:	$(MAIN)
	@echo Simple compilier named mycc has been compiled

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUT_DIR)/$(MAIN) $(SRCS)

clean:
	$(RM) $(SRC_DIR)*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

