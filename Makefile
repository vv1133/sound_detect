CC = gcc
CFLAGS =  -std=c99 -I. -lbcm2835
DEPS = 
OBJ = detect.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

detect: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
