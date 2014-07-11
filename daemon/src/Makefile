OBJECTS = test.o ModCom.o arduino-serial-lib.o ModDev.o ActuatorRele.o LedControl.o
LIBS =

INCLDIC = ./../include

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