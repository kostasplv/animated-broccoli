CC		= gcc
FLAGS	= -c -g  
COMP = -o
OUT = ngrams
IN = main.o ngrams.o unit_testing.o

ngrams: main.o ngrams.o unit_testing.o
	$(CC) $(COMP) $(OUT) $(IN) -lcunit

unit_testing.o:	unit_testing.c
	 $(CC) $(FLAGS) unit_testing.c 
main.o: main.c
	$(CC) $(FLAGS) main.c

ngrams.o: ngrams.c
	$(CC) $(FLAGS) ngrams.c

# clean up
clean:
	rm -f $(OUT) $(IN)

