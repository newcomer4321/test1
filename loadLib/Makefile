target= test
CC=gcc
CFLAGS=-g 
OBJS = loadLib.o

${target}:$(OBJS)
	$(CC)  -o  $@   $^ $(CFLAGS)  -ldl

clean:

	rm -rf $(OBJS) $(target)
