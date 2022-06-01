CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -Wall -o0
all: startup.o main.o
startup.o : startup.c
	$(CC) $(CFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -f *.o
