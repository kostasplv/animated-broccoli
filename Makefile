CC		= gcc
FLAGS	= -c -g  
COMP = -o
OUT = ngrams
OUT1= exe
IN = main.o ngrams.o 
IN1= unit_testing.o ngrams.o

ngrams: main.o ngrams.o unit_testing.o
	$(CC) $(COMP) $(OUT) $(IN)
	$(CC) $(COMP) $(OUT1) $(IN1) -lcunit
unit_testing.o:	unit_testing.c
	 $(CC) $(FLAGS) unit_testing.c 

main.o: main.c
	$(CC) $(FLAGS) main.c

ngrams.o: ngrams.c
	$(CC) $(FLAGS) ngrams.c

# clean up
clean:
	rm -f $(OUT) $(OUT1) $(IN) unit_testing.o

