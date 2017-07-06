#include "standards.h"
#include<time.h>

/* Outputs a divider to the output file */
void outputDivider(FILE* fptr, char ch, unsigned int total)
{
	int i;
	
	if(fptr != NULL)
	{
		while(total-- > 0) fputc(ch, fptr);
		fputc('\n', fptr);
	}
}

/* Outputs a menu to the output file */
void outputMenu(FILE* fptr)
{
	if(fptr != NULL)
	{
		outputDivider(fptr, CH_OUT, WIDTH);
		
		printf("Encryption Menu\n1. Encrypt (Screen)\n2. Decrypt (Screen)\n3. Encrypt (File)\n4. Decrypt (File)\n5. Special Encryption (File)\n6. Quit\n");
		
		outputDivider(fptr, CH_OUT, WIDTH);
	}
}

/* Outputs the current time/date to the output file */
void logTime(FILE* fptr)
{
	time_t timer;
	struct tm* tm_info;
	
	char t[26];
	
	if(fptr)
	{
		timer = time(&timer);
		tm_info = localtime(&timer);
	
		strftime(t, 26, "%m%d%Y%H%M%S", tm_info);
		fprintf(fptr, "%s", t);
	}
	else
	{
		printf("Error logging current time. File was not set.\n");
	}
}

void flushScreenInput()
{
	int ch;
	while((ch = getchar()) != EOF && ch != '\n');
}

/* Admin rights; password sequence */
int get_sequence()
{
	int i, done, password;
	
	done = password = 0;
	
	while((i = getchar()) != EOF && i != '\n')
	{
		if(i == 27)
		{
			i = getchar();
			i = getchar();
		}
		
		password += i;
	}
	
	return password;
}
