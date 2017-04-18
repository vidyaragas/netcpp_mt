# source files.
SRC = BaseSocket.cc ServerSocket.cc ClientSocket.cc NetPool.cc NetInterface.cc ThrMessageQueue.cc ThrQueueController.cc 
OBJ = $(SRC:.cc=.o)
   
OUT = libutils.a 
   
# include directories
INCLUDES = -I. -I../include/ -I/usr/local/include
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -pg -std=c++11 -Wall
  
#  # compiler
CCC = g++
 
# library paths
LIBS = -L../ -L/usr/local/lib

# libraries
LDLIBS = -lm
 
#  # compile flags
LDFLAGS = -pg -pthread
 
.SUFFIXES: .cc
 
default: $(OUT)
 
.cc.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
 
clean:
	rm -f $(OBJ) $(OUT) Makefile.bak
