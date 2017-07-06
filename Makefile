all: encryption
	
encryption: encryption.c
	gcc -std=c89 -o encryption encryption.c mapped_encryption.c standards.c mapped_encryption.h -g
	
clean:
	rm -f encryption
