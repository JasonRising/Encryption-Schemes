#ifndef mapped_encryption_h_
#define mapped_encryption_h_
#include<stdio.h>
#define BUF_SIZE 1024
#define MAP_SIZE 95
#define OFFSET 32
#define MAX 127
#define SEED 95

int fill_map();
int gen_ran_map();
int encrypt(char ch);
int decrypt(char ch);

void encrypt_file(FILE* in, FILE* out, int flag);
void decrypt_file(FILE* in, FILE* out, int flag);

#endif
