CC = gcc
CFLAGS = -g -Wall
TARGET = testlib


$(TARGET) : list.o bitmap.o hash.o debug.o hex_dump.o main.o structure_helper.o bitmap_helper.o hash_helper.o list_helper.o
			  $(CC) $(CFLAGS) -o $(TARGET) list.o bitmap.o hash.o debug.o hex_dump.o main.o structure_helper.o bitmap_helper.o hash_helper.o list_helper.o


main.o : main.c list.h bitmap.h hash.h list_helper.h bitmap_helper.h hash_helper.h structure_helper.h
			$(CC) $(CFLAGS) -c -o main.o main.c

list.o : list.c list.h
			$(CC) $(CFLAGS) -c -o list.o list.c

bitmap.o : bitmap.c bitmap.h
			$(CC) $(CFLAGS) -c -o bitmap.o bitmap.c

hash.o : hash.c hash.h
			$(CC) $(CFLAGS) -c -o hash.o hash.c

debug.o : debug.c debug.h
			$(CC) $(CFLAGS) -c -o debug.o debug.c

hex_dump.o : hex_dump.c hex_dump.h
			$(CC) $(CFLAGS) -c -o hex_dump.o hex_dump.c

structure_helper.o : structure_helper.c structure_helper.h main.h list.h bitmap.h hash.h
			$(CC) $(CFLAGS) -c -o structure_helper.o structure_helper.c

bitmap_helper.o : bitmap_helper.c bitmap_helper.h  main.h bitmap.h round.h hex_dump.h
			$(CC) $(CFLAGS) -c -o bitmap_helper.o bitmap_helper.c

hash_helper.o : hash_helper.c hash_helper.h main.h hash.h
			$(CC) $(CFLAGS) -c -o hash_helper.o hash_helper.c

list_helper.o : list_helper.c list_helper.h main.h list.h
			$(CC) $(CFLAGS) -c -o list_helper.o list_helper.c

clean:
	rm -f *.o
	rm -f $(TARGET)


