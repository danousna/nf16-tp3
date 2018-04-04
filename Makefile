CC = gcc
CFLAGS = -Wall
DEPS = blockchain.h interface.h
OBJ = main.o blockchain.o interface.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

tp3: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean: 
	@rm -f tp3