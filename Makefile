CC=gcc
CFLAGS=-I.
DEPS = i2c.h
OBJ = as7265x.o i2c.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: as7265x_reg as7265x_reading

as7265x_reg: as7265x_reg.o as7265x.o i2c.o
	$(CC) -o $@ $^ $(CFLAGS)

as7265x_reading: as7265x_reading.o as7265x.o i2c.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm $(OBJ) as7265x_reg as7265x_reading
