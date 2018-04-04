CC = gcc
CFLAGS = -Wall
DEPS = tp3.h
OBJ = main.o tp3.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tp3: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean: 
	@rm -f tp3