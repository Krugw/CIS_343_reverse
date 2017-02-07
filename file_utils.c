#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include <sys/stat.h>

int read_file( char* filename, char **buffer )
{
    //attempt to open the file as 'read only' with error handling
	FILE *fp = fopen (filename,"r");
	if (!fp)
	{
		fprintf(stderr, "Error Opening File!");
		return 1;
	}

	//get size of buffer
	struct stat st;
	stat(filename, &st);
	int fileSize = st.st_size;

	//make sure the buffer is null
	*buffer = NULL;

	//malloc the buffer! W/ error handling
	*buffer = (char *)malloc(fileSize);
	if (!*buffer)
	{
		fclose(fp);
		fprintf(stderr,"Error with malloc!");
		return 1;
	}

	//read the entire file into the buffer w/ error handling
	if(fread( *buffer ,fileSize, 1 , fp)!=1)
	{
		fclose(fp);
		free(*buffer);
		fprintf(stderr,"Error reading from file!");
		return 1;
	}
	//close the file pointer
	fclose(fp);
	//Success!
	return 0;
}
int write_file( char* filename, char *buffer, int size) {
    //open the file as 'write + create if doesn't exist!' w/ error handling
	FILE *fp = fopen (filename, "w+");
	if (!fp)
		{
			fprintf(stderr, "Error Opening File!");
			return 1;
		}
    //write the buffer to the file
	fwrite(buffer, size, 1, fp);
	//close file the pointer
	fclose(fp);
	//Successes!
	return 0;
}
