#include "mapped_encryption.h"
#include "standards.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define PATH_LENGTH 101

char* get_arrow(int i);

int main(void)
{
	extern char map[MAP_SIZE];
	extern char buf[BUF_SIZE];
	char path[PATH_LENGTH];
	int ch;
	int i, flag;
	FILE* in, *out;
	flag = 0;
		
	if(flag = fill_map(map))
	{
		printf("Map Encoding not found; new sequence generated.\n");
				
		if(gen_ran_map())
		{
			printf("Error With Input File. Make sure \"map\" is in same directory.\n");
		}
		else
		{
			out = fopen("Data/log_file.txt", "w");
			logTime(out);
			fclose(out);
			out = NULL;
			
			flag = fill_map(map);
		}
	}
	
	if(flag)
	{
		printf("Error: Could not fill map.\n");
	}
	else
	{		
		path[PATH_LENGTH - 1] = 0;
		
		do
		{
			outputMenu(stdout);
			ch = getchar();
			flushScreenInput();
			switch(ch)
			{
				case '1':
					printf("Enter a text (ENTER + ctrl + d):\n");
					encrypt_file(stdin, stdout, 0);
					break;
				case '2':
					printf("Enter a text (ENTER + ctrl + d):\n");
					decrypt_file(stdin, stdout, 0);
					break;
				case '3':
					printf("Enter File Path followed: \n");
					
					fgets(path, PATH_LENGTH, stdin);
					path[strlen(path)-1] = 0;
					
					/*Open the input file*/
					if(in = fopen(path, "r"))
					{
						/*Open the output file*/
						out = fopen("out", "w");
						
						printf("Enter 0 or 1: ");
						
						/*0 or 1*/
						i = getchar();
						
						encrypt_file(in, out, i);
						
						fclose(in);
						fclose(out);
						
						printf("File %s encrypted. Check \"out\" for results.\n", path);
					}
					else
					{
						printf("\nERROR: --'%s' doesn't exist--\n", path);
					}
					
					flushScreenInput();

					break;
				
				case '4':
					printf("Enter File Path: \n");
					fgets(path, PATH_LENGTH, stdin);
					path[strlen(path)-1] = 0;
					
					/*Open the input file*/
					if(in = fopen(path, "r"))
					{
						/*Open the output file*/
						out = fopen("in", "w");
						
						printf("Enter 0 or 1: ");
						
						/*0 or 1*/
						i = getchar();
						
						/*if(i)
						{
							printf("Enter Code: ");
							srand(SEED);				
						}*/
						
						decrypt_file(in, out, i);
						
						fclose(in);
						fclose(out);
						
						printf("File %s decrypted. Check \"in\" for results.\n", path);
					}
					else
					{
						printf("\nERROR: --'%s' doesn't exist--\n", path);
					}
					
					break;
				
				case '5':
					break;
				
				case 27:
					printf("Secret Code Entered\nEnter Sequence below:\n");
					outputDivider(stdout, CH_OUT, WIDTH/2);
					if(get_sequence() == 266)
					{
						if(gen_ran_map() || fill_map(map))
						{
							printf("Error Processing your request.\n");
							ch = QUIT;
						}
						else
						{
							printf("Success.\n");
						}
					}
					break;
				case QUIT:
				default:
					break;
			}

			if(ch != QUIT)
			{
				printf("\nPress any key to continue: ");
				flushScreenInput();
			}
			
			system("clear");
			
		}while(ch != QUIT);
	}
	
	/*if((i = getchar()) == 27)
	{
		i = getchar();
		i = getchar();
		
		printf("%s\n", get_arrow(i));
	}
	*/
	
	return 0;
}

char* get_arrow(int i)
{
	char* arrow;
	switch(i)
	{
		case 'A':
			arrow = "Up";
			break;
		case 'B':
			arrow = "Down";
			break;
		case 'C':
			arrow = "Right";
			break;
		case 'D':
			arrow = "Left";
			break;
		default:
			arrow = 0;
			break;
		
	}
	
	return arrow;
}
