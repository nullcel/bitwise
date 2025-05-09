CC=gcc
CFLAGS=-O2 -Wall
OBJS=main.o encrypt.o

encryptor: $(OBJS)
	$(CC) -o encryptor $(OBJS)

main.o: main.c encrypt.h
	$(CC) $(CFLAGS) -c main.c

encrypt.o: encrypt.c encrypt.h
	$(CC) $(CFLAGS) -c encrypt.c

clean:
	rm -f *.o encryptor
