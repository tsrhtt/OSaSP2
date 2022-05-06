#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough arguments
	if (argc != 3)
	{
		fputs("Wrong or missing arguments! Use: z3.exe [filename] [num of lines] \n", stderr);
		return -1;
	}
	char *filename = argv[1];
	int linesnum = 0;
	if (sscanf( argv[2], "%u", &linesnum ) != 1)
	{
		fputs("Cant read num of lines!\n", stderr);
		return -1;
	}
	// trying to open file
	printf("Opening file %s...\n", filename);
	FILE* infile = fopen (filename, "r");
	if (!infile)
	{
		fputs("Cant open file!\n", stderr);
		return -1;
	}
	fputs("File openned!\n", stderr);
	puts("[file start]");
        int linesctr = 0;
	// printing sets of lines
	while (1) 
	{
		int nextchar = fgetc(infile);
		
		if ( nextchar == EOF ) 
		{
			break;
		}
		if ( linesnum && (nextchar == '\n') && !(++linesctr % linesnum) )
		{
			printf("\n[%i lines printed. Press any key to continue...]", linesnum);
			getchar();
			continue;
		}
		putchar(nextchar);
	}
	// end
	puts("\n[file end]");	
	// close file
	if (fclose(infile))
		fputs("Error: file closed unexpectedly!\n", stderr);	

	return 0;
}
