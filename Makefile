CC=gcc
CFLAGS=-I.
DEPS = i2c.h
OBJ = as7265x.o i2c.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

as7265x: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

