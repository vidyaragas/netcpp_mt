# source files.
SRC = ClientApp.cc  	
OBJ = $(SRC:.cc=.o)
   
OUT = ClientApp 
   
# include directories
INCLUDES = -I. -I../netutils -I/usr/local/include
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -pg -std=c++11 -Wall
  
#  # compiler
CCC = g++
 
# library paths
LIBS = -L../netutils -L/usr/local/lib

# libraries
LDLIBS = -lm -lutils
 
#  # compile flags
LDFLAGS = -pg -pthread
 
.SUFFIXES: .cc
 
default: $(OUT)
 
.cc.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	$(CCC) $(LDFLAGS) -o $(OUT) $(OBJ) $(LIBS) $(LDLIBS)
#	ar rcs $(OUT) $(OBJ)
 
clean:
	rm -f $(OBJ) $(OUT) Makefile.bak
