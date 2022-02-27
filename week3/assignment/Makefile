cc = g++
target = a.out

objects = main.o str.o

cflags = -c -O2 -w

$(target) : $(objects)
	$(cc) -o $(target) $(objects)

.cpp.o :
	$(cc) $(cflags) -o $@ $<

$(objects) : Str.h

.PHONY : clean
clean :
	rm $(objects) $(target)
