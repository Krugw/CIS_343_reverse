#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv) {
    //check for valid number of cmd line arguments
	if(argc < 3) {
		printf("Please enter a valid source and destination file.\n");
		exit(1);
	}
	//init buffer to be malloced in red_file()
	char *buffer;
	read_file(argv[1],&buffer);

    //get size of buffer using string.h
	size_t size = strlen(buffer);

	//malloc new buffer to be same size as original buffer
	char *rbuffer = (char*)malloc((size+1)*sizeof(char));
	int i;

	//set ith character to be 'size-i-1'th character of original buffer
	//-1 to account for \0 at the end
	for(i = 0; i < size+1; i++)
	{
		rbuffer[i] = buffer[size - 1 - i];
	}
	//append \0 to the end b/c C strings are stupid
	rbuffer[i] = '\0';

	write_file(argv[2],rbuffer,size);

	//No garbage collection in c! Gotta do it yourself.
	free(buffer);
	free(rbuffer);
}
