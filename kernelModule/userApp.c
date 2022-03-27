/*
* ioctl.c - the process to use ioctl's to control the kernel module
*
* Until now we could have used cat for input and output. But now
* we need to do ioctl's, which require writing our own process.
*/
/*
* device specifics, such as ioctl numbers and the
* major device file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* open */
#include <unistd.h> /* exit */
#include <sys/ioctl.h> /* ioctl */
#include <errno.h>
#include <string.h>


#define DEVICE_FILE_NAME "/dev/primeAccel"
#define COMPUTE_CMD 0
#define CLEAR_MEM_CMD 1
#define READ_CMD 2
/*
* Functions for the ioctl calls
*/
void ioctl_COMPUTE_CMD (int file_desc)
{
	int ret_val;
	ret_val = ioctl(file_desc, 0, COMPUTE_CMD);
	if (ret_val < 0)
	{
		printf("ioclt error : %s\n", strerror(errno));
	
	}
}
void ioctl_CLEAR_MEM_CMD (int file_desc)
{
	int ret_val;
	ret_val = ioctl(file_desc, 0, CLEAR_MEM_CMD);
	if (ret_val < 0)
	{
		printf("ioclt error : %s\n", strerror(errno));
	
	}
}
void ioctl_READ_CMD (int file_desc)
{
	int ret_val;
	ret_val = ioctl(file_desc, 0, READ_CMD);
	if (ret_val < 0)
	{
		 printf("ioclt error : %s\n", strerror(errno));
		
	}
}
/*
* Main - Call the ioctl functions
*/
int main()
{
	int Choice;
	int exitflag=1;
	int file_desc;


	printf("######################################## \n\r");
	printf("      Prime Sieve Accelerator Demo  \n\r");
	printf("######################################## \n\r");
	file_desc = open(DEVICE_FILE_NAME, O_RDWR | O_SYNC);
	if (file_desc < 0) 
	{
		printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
		exit(-1);
	}


	printf("send clear PE memory via kernel module\n");
	ioctl_CLEAR_MEM_CMD(file_desc);
	printf("send compute all to PE via kernel module\n");
	ioctl_COMPUTE_CMD	(file_desc);
	printf("send read PE memory via kernel module\n");
	ioctl_READ_CMD (file_desc);


	close(file_desc);
	printf("################################ \n\r");
	printf("      Bye Prime Sieve Accelerator Demo  \n\r");
	printf("################################ \n\r");
	return 0;
}

