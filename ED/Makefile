CPP = g++
CFLAGS = -Wall -g

ARPACKPP_DIR = /usr/local/arpack++
#!! relative location of arpack++ file, it may be called arpackpp...

PLAT         = linux
ARPACKPP_INC = $(ARPACKPP_DIR)/include
CPP_WARNINGS = -ansi -pedantic-errors
CPP_FLAGS    = -D$(PLAT) -I$(ARPACKPP_INC) $(CPP_WARNINGS)

AREIGFUN_DIR = $(ARPACKPP_DIR)/examples/areig

YED_ROOT = ../

objects = publicFuncs.o

all : $(objects)
.PHONY : all

publicFuncs.o : publicFuncs.cpp ED.h
	$(CPP) $(CFLAGS) $(CPP_FLAGS) -I$(AREIGFUN_DIR) -I$(YED_ROOT) -c publicFuncs.cpp

.PHONY : clean
clean :
	rm $(objects)
