#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough arguments
	if (argc != 2)
	{
		fputs("Wrong or missing arguments! Use: ./z2.exe [filename]\n", stderr);
		return -1;
	}
	char *filename = argv[1];
	// trying to open file
	printf("Opening file %s...\n", filename);
	FILE* outfile = fopen (filename, "w");
	if (!outfile)
	{
		fputs("Cant open file!\n", stderr);
		return -1;
	}
	fputs("File openned!\n", stderr);
	int error = 0;
	while (!error) 
	{
		// read char
		int nextchar = getchar();
		if (nextchar == EOF)
		{
			error = 1; 
			break;
		}
		// exit key
		if ( nextchar == '.' )
			break;
		if (fputc( nextchar , outfile) == EOF)
		{
			error = 1; 
			break;
		}
	}
	if (error)
		fputs("An exception has occured!", stderr);
	system("/bin/stty cooked");
	if (fclose(outfile))
		fputs("Error: file closed unexpected!\n", stderr);	

	return 0;
}
