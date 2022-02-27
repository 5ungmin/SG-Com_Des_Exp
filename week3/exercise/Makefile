CC = g++
TARGET = RArray

OBJECTS = main.o array.o rangearray.o
SRC = main.cpp array.cpp rangearray.cpp

CFLAGS = -c

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

.cpp.o :
	$(CC) $(CFLAGS) -o $@ $<

$(OBJECTS) : Array.h RangeArray.h

.PHONY : clean
clean :
	rm $(OBJECTS) $(TARGET)

