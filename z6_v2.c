#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dirent.h>

#include <string.h>

#include <limits.h> // here is PATH_MAX

#include <time.h> 

int findFile( char *dirname, const char *filename, int *ctr_visited )
{
	DIR * dir_cur = opendir(dirname);  
	if (!dir_cur)
		return 0;
	struct dirent *d;
	while (d = readdir(dir_cur))
	{
		char *cur_elname = d->d_name;
		if ( d->d_type & DT_DIR && strcmp(cur_elname, ".") && strcmp(cur_elname, "..") )
		{
			char path[PATH_MAX];
			if (snprintf(path, PATH_MAX, "%s/%s", dirname, cur_elname) < 0)
				return 0;

			if (findFile(path, filename, ctr_visited))
				return 1;
		}
		else if ( d->d_type & DT_REG && !strcmp(cur_elname, filename) )
		{
			return 1;
		} 
		
		(*ctr_visited)++;
	}
	if (closedir(dir_cur))
		fputs("Error: directory closed unexpectedly!\n", stderr);
		
	return 0;	
}

void strmode(mode_t mode, char *perm)
{
	for (int i = 0; i < 10; i++)
		perm[i] = '-'; 	
	if (mode & 0400)
		perm[1] = 'r';  	
	if (mode & 0200)
	  	perm[2] = 'w';
	if (mode & 0100)
	  	perm[3] = 'x';
	if (mode & 0040)
	  	perm[4] = 'r';
	if (mode & 0020)
	  	perm[5] = 'w';
	if (mode & 0010)
	  	perm[6] = 'x';
	if (mode & 0004)
	  	perm[7] = 'r';
	if (mode & 0002)
	  	perm[8] = 'w';
	if (mode & 0001)
	  	perm[9] = 'x';
}


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	// check if it is enough arguments
	if (argc != 3)
	{
		fputs("Wrong or missing arguments! Use: ./z6_v2.exe [initial directory] [filename]\n", stderr);
		return -1;
	}
	char *filename = argv[2];
	int ctr_visited = 0;
	// find 
	if ( findFile( argv[1] ,filename , &ctr_visited ) )
	{
		printf("file %s founded!\n", filename);
		printf("visited %i records!\n", ctr_visited);
		puts("File stats: ");
		// getting access rights
		struct stat bufstat;
		if ( lstat( filename, &bufstat ) )
		{
			fputs("Can't read file stats!\n", stderr);
			return -1;
		}
		char modebuf[16] = { 0 };
		strmode(bufstat.st_mode, modebuf);

		char realpathbuf[PATH_MAX];
		if (realpath(filename, realpathbuf))
			printf("\tFull path:\t%s\n", realpathbuf);
		else
			printf("\tFull path:\tCan not resolve full path!\n");

		char *date = ctime(&bufstat.st_ctime);
		printf("\tDate of birth:\tIsn't supported!\n");
		if (date)
			printf("\tDate st change:\t%s", date);
		else
			printf("\tDate st change:\tfailed to recognize\n");

		printf("\tDesc No:\t%lu\n",  bufstat.st_ino);
		printf("\tAccess rights:\t%s\n",  modebuf);
		printf("\tSize:\t\t%li bytes\n", (bufstat.st_size) );
		
		
		
	}
	else
	{
		puts("File not founded!");
	}

	return 0;
}
