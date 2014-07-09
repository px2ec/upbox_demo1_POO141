OBJECTS = upboxd.o
LIBS =

INCLDIC = ./

CC = gcc
CPP = g++
CFLAGS = -Wall -O2
CXXFLAGS = -Wall -O2
LDFLAGS =

all: test

test: $(OBJECTS)
	$(CPP) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o test

rebuild:
	make clean && make

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCLDIC) -c $<

%.o: %.cpp
	$(CPP) $(CXXFLAGS) $(LDFLAGS) -I$(INCLDIC) -c $<