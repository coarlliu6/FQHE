CPP = g++
CFLAGS = -Wall -g

BOOST_ROOT = /usr/local/boost_1_56_0 # !! it is the relative location of boost file

objects = constr.o tool.o dGen.o tGen.o publicFuncs.o

all : $(objects)
.PHONY : all

constr.o : constr.cpp basis.h
	$(CPP) $(CFLAGS) -c constr.cpp

tool.o : tool.cpp basis.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c tool.cpp

dGen.o : dGen.cpp basis.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c dGen.cpp

tGen.o : tGen.cpp basis.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c tGen.cpp

bGen.o : bGen.cpp basis.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c bGen.cpp

publicFuncs.o : publicFuncs.cpp basis.h
	$(CPP) $(CFLAGS) -c publicFuncs.cpp

.PHONY : clean
clean :
	rm $(objects)
