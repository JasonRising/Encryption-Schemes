#include "mapped_encryption.h"

char map[MAP_SIZE] = {0};
char buf[BUF_SIZE] = {0};

int fill_map()
{
	FILE* fin;
	int i, code;
	char c;
	
	code = 1;
	
	if(fin = fopen("Data/map", "r"))
	{
		for(i = 0; i < MAP_SIZE && (c = fgetc(fin)) != EOF; i++)
		{
			map[i] = c;
		}
		
		if(i == MAP_SIZE) code = 0;
		
		fclose(fin);
	}
	
	return code;
}

int gen_ran_map()
{
	FILE* fout;
	
	int i, j, t, code;
	
	srand(time(NULL));
	
	for(i = 0; i < MAP_SIZE; i++)
	{
		map[i] = i+OFFSET;
	}
	
	for(i = 0; i < MAP_SIZE; i++)
	{
		j = map[i];
		map[i] = map[t = rand() % MAP_SIZE];
		map[t] = j;
	}
	
	code = 1;
	
	if(fout = fopen("Data/map", "w"))
	{
		code = 0;
		for(i = 0; i < MAP_SIZE; i++)
		{
			fputc(map[i], fout);
		}
		
		fclose(fout);
	}
	
	return code;
}

int encrypt(char ch)
{
	return map[ch - OFFSET];
}

int decrypt(char ch)
{
	int i, found;
	char val;
	
	found = 0;
	val = 'X';
	
	for(i = 0; i < MAP_SIZE && !found; i++)
	{
		if(map[i] == ch)
		{
			found = 1;
			val = (char)(i+OFFSET);
		}
	}
	
	return val;
}

void encrypt_file(FILE* in, FILE* out, int flag)
{
	int i, ch, n;
	
	if(in != NULL && out != NULL)
	{
		i = fread((void*)buf, 1, BUF_SIZE-1, in);
	
		if(!feof(in) || !ferror(in))
		{
			for(ch = 0; ch < i; ch++)
			{
				if(buf[ch] >= OFFSET && buf[ch] < MAX)
				{
					n = rand() % 10 + 1;
					
					do
					{
						buf[ch] = encrypt(buf[ch]);
					} while(flag && --n > 0);
				}
			}
		
			fwrite((void*)buf, 1, i, out);
		}
	}
}

void decrypt_file(FILE* in, FILE* out, int flag)
{
	int ch, i, n;
	
	srand(SEED);
	
	if(in != NULL && out != NULL)
	{
		i = fread((void*)buf, 1, BUF_SIZE-1, in);
	
		if(!feof(in) || !ferror(in))
		{
			for(ch = 0; ch < i; ch++)
			{
				if(buf[ch] >= OFFSET && buf[ch] < MAX)
				{
					n = rand() % 10 + 1;
					
					do
					{
						buf[ch] = decrypt(buf[ch]);
					} while(flag && --n > 0);
				}
			}
		
			fwrite((void*)buf, 1, i, out);
		}
	}
}
