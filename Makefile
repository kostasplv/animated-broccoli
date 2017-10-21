CC		= gcc
FLAGS	= -c
COMP = -o
OUT = exe
IN = main.o ngrams.o

exe: main.o ngrams.o
	$(CC) $(COMP) $(OUT) $(IN)

main.o: main.c
	$(CC) $(FLAGS) main.c

ngrams.o: ngrams.c
	$(CC) $(FLAGS) ngrams.c

# clean up
clean:
	rm -f $(OUT) $(IN)

