#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dirent.h>


int main( int argc , char *argv[ ] , char *envp[ ] )
{
	DIR * dir_cur   = opendir(".");  
	DIR * dir_root  = opendir("/");  
	if (!dir_cur || !dir_root)
	{
		fputs("Can't open directory!\n", stderr);
		return -1;
	}
	fputs("Directories openned successfully!\n", stderr);
	struct dirent *d;
	puts("> Current directory");
	while (d = readdir(dir_cur))
	{
		puts(d->d_name);
	}
	puts("> Root directory");
	while (d = readdir(dir_root))
	{
		puts(d->d_name);
	}
	if (closedir(dir_cur) || closedir(dir_root))
		fputs("Error: directory closed unrxpectedly!\n", stderr);	

	return 0;
}
