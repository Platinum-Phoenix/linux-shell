objects = main.o

all : shell

shell : $(objects)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -o $@ -c $<

clean :
	rm -rf $(objects) shell
