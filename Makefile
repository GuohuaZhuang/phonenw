phonenw: src/main.c \
		 src/phonenw.c \
		 src/phonenw.h \
		 src/trie.c \
		 src/trie.h 
	gcc src/main.c src/phonenw.c src/trie.c -o bin/phonenw -g3 -O0 -Wall

clean:
	rm bin/phonenw

