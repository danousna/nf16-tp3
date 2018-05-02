CC = gcc
CFLAGS = -Wall
DEPS = blockchain.h interface.h tests.h
OBJ = main.o blockchain.o interface.o tests.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tp3: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean: 
	@rm -f tp3