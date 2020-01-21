/*
 * run.c
 * This is open-source program that help quick execute source file
 * with just only one command.
 * You can clone, uses, modify and distribute it.
 * 
 * Copyright: Binh-Thanh Mai Nguyen (binhmainguyen193@gmail.com).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define C 		1
#define Python 	2


/* 
 * Describe: This function is used to detecting source file format
 * @source: the source input
 */
static int exe_dect(char *source)
{
	int ret = 0, count = 0, tmp;
	int len = strlen(source);
	char *buff;
	
	/* Catching dot character */
	for(int i=len; i>=0; i--)
	{
		if(source[i] == '.')
		{
			break;
		}
		count ++;
	}
	
	buff = malloc(count);
	tmp = count;
	
	/* Get file format */
	for(int i=len; i>=(len-count); i--)
	{
		buff[tmp] = source[i];
		tmp--;
	}
	
	/* Detecting file format */
	if(!strcmp(buff, ".c"))
	{
		ret = C;
		goto out;
	}
	
	else if(!strcmp(buff, ".py"))
	{
		ret = Python;
		goto out;
	}
	
	printf("Executable file does not supported !!!\n");
	
	out:
		free(buff);
		return ret;
}


/*
 * Describe: This function is used to cut (*.c) extention to get only filename
 * @source: source file input
 */
static char *strcut(char *source)
{
	int length = strlen(source);
	char *filename = malloc(length - 2);
	
	/* Execute to split file exetention "*.c" */
	for(int i=0; i<(length-2); i++)
	{
		filename[i] = source[i];
	}
	
	return filename;
}


/*
 * Describe: This function is used to generating
 * build command of C code and execute generated command
 * @Source: source file input
 * @filename: executable output file name
 */
static void build_cmd(char *source, char *filename)
{
	/* Build command syntax components */
	char *gcc = "gcc ";
	char *obj = " -o ";
	
	/* Setup build command */
	int len_gcc = strlen(gcc);
	int len_obj = strlen(obj);
	int len_filename = strlen(filename);
	int len_source = strlen(source);
	int len = len_gcc + len_obj + len_filename + len_source;
	char cmd[len];
	
	/* Merge build command */
	strcpy(cmd, gcc);
	strcat(cmd, source);
	strcat(cmd, obj);
	strcat(cmd, filename);
	
	system(cmd); 			// Build executable file
}


/* Describe: This function is used to delete executable file
 * @filename: executable output file name  
 */
static void exe_remove(char *filename)
{
	char *rm = "rm -rf ";			  // Base command for remove executable file
	
	/* Setup remove execute file command */
	int len_rm = strlen(rm);
	int len_name = strlen(filename);
	int len_cmd = len_rm + len_name;
	char rm_cmd[len_cmd];
	
	/* Merge command */
	strcpy(rm_cmd, rm);
	strcat(rm_cmd, filename);
	
	system(rm_cmd);	//Remove executable file
}


/* Describe: This function is used to execute the executable file
 * following the according to the type of source file language
 * @type: type of source file language
 * @filename: The executable file input
 */
static int file_exect(int type, char *filename)
{
	/* Base execute command */
	char *ec = "./";				// Base command for execute C
	char *py = "python ";			// Base command for python execute
	char *exe;
	int len_exe;
	
	switch(type)
	{
		case C: 
			len_exe = strlen(ec);
			exe = ec;
			break;
		
		case Python:
			len_exe = strlen(py);
			exe = py;
			break;
	}
	
	/* Merge command component */
	int len_filename = strlen(filename);
	int len_cmd = len_exe + len_filename;
	char cmd[len_cmd];
	strcpy(cmd, exe);
	strcat(cmd, filename);
	
	system(cmd);	// execute command
	
	return 0;
}


int main(int argc, char *argv[])
{
	char *exe_file;
	int type;
	
	type = exe_dect(argv[1]);
	switch(type)
	{
		case C:
			exe_file = strcut(argv[1]);
			build_cmd(argv[1], exe_file);
			file_exect(type, exe_file);
			exe_remove(exe_file);
			break;
		
		case Python:
			file_exect(Python, argv[1]);
			break;
	}
		
	return 0;
}
