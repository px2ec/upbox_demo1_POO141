
TARGET = upboxd

OBJECTS = $(TARGET).o ModCom.o arduino-serial-lib.o ModDev.o ActuatorRele.o LedControl.o Dommo.o TempSensor.o
LIBS = -ljson

SRCDIR = ./src

VPATH := $(SRCDIR)

INCLDIC = ./../include

CC = gcc
CPP = g++
CFLAGS = -Wall -O2
CXXFLAGS = -Wall -O2
LDFLAGS =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(TARGET)

rebuild:
	make clean && make

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCLDIC) -c $<

%.o: %.cpp
	$(CPP) $(CXXFLAGS) $(LDFLAGS) -I$(INCLDIC) -c $<