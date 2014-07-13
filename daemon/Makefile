
SRCDIR = ./src

TARGET = upboxd

all: $(TARGET)

$(TARGET):
	cd $(SRCDIR) && make
	mv $(SRCDIR)/$(TARGET) .

clean:
	cd $(SRCDIR) && make clean
	rm -rf $(TARGET)

rebuild:
	make clean && make