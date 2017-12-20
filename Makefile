CFLAGS = -g -Wall

all: compile 

compile: tokenizer.c sorted-list.c Indexer.h Indexer.c 
	gcc $(CCFLAGS) tokenizer.c sorted-list.c Indexer.c -o index


clean:
	rm -rf index 
