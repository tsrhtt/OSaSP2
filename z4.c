#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough arguments
	if (argc != 3)
	{
		fputs("Wrong of missing arguments! Use: ./z4.exe [sender filename] [receiver filename]\n", stderr);
		return -1;
	}
	char *filename_in  = argv[1];
	char *filename_out = argv[2];
	if (!strcmp(filename_in, filename_out))
	{
		fputs("Exception: files have the same names!\n", stderr);
		return -1;
	}	
	FILE* file_in  = fopen (filename_in , "r");
	FILE* file_out = fopen (filename_out, "w");
	if (!file_in || !file_out)
	{
		fputs("Can't open file!\n", stderr);
		return -1;
	}
	fputs("Files openned!\n", stderr);
	struct stat bufstat;
	if ( stat( filename_in, &bufstat ) )
	{
		fputs("Can't read file stats!\n", stderr);
		return -1;
	}
	if ( chmod( filename_out, bufstat.st_mode ) )
	{
		fputs("Can't set file stats!\n", stderr);
		return -1;
	}
	int nextchar;
	while ( (nextchar = fgetc(file_in)) != EOF ) 
	{
		// print char to file 
		if (putc(nextchar, file_out) == EOF)
		{
			fputs("Exception: can't write into file!\n", stderr);
			return -1;
		}
	}
	puts("Done!");
	if (fclose(file_out) || fclose(file_in))
		fputs("Error: file closed unexpectedly!\n", stderr);	

	return 0;
}
