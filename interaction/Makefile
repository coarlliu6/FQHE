CPP = g++
CFLAGS = -Wall -g

BOOST_ROOT = /usr/local/boost_1_56_0 # !! relative location of boost file

objects = vmIntegrand.o dItr.o sItr.o tItr.o publicFuncs.o

all : $(objects)
.PHONY : all

vmIntegrand.o : vmIntegrand.cpp interaction.h
	$(CPP) $(CFLAGS) -c vmIntegrand.cpp

dItr.o : dItr.cpp interaction.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c dItr.cpp

sItr.o : sItr.cpp interaction.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c sItr.cpp

tItr.o : tItr.cpp interaction.h
	$(CPP) $(CFLAGS) -c tItr.cpp

publicFuncs.o : publicFuncs.cpp interaction.h
	$(CPP) $(CFLAGS) -c publicFuncs.cpp

.PHONY : clean
clean :
	rm $(objects)
