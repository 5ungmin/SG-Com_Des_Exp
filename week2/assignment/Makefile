cc=gcc
cflags = -O2 -w
target = StarWars.exe
objects = main.o read.o calculate.o print_result.o

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

.PHONY : clean
clean :
	rm $(target) $(objects)

