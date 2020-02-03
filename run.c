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

#include "run.h"


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

	else if(!strcmp(buff, ".sh"))
	{
		ret = Bash;
		goto out;
	}

	else if(!strcmp(buff, ".cpp"))
	{
		ret = Cpp;
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
static char *strcut(int type, char *source)
{
	int length = strlen(source);
	char *filename;
	
	/* Execute to split file exetention "*.c" */
	switch(type)
	{
		case C:
			filename = malloc(length - 2);
			for(int i=0; i<(length-2); i++)
			{
				filename[i] = source[i];
			}
			break;
		
		case Cpp:
			filename = malloc(length - 2);
			for(int i=0; i<(length-4); i++)
			{
				filename[i] = source[i];
			}
			break;
	}
	
	
	return filename;
}


/*
 * Describe: This function is used to generating
 * build command of C code and execute generated command
 * @Source: source file input
 * @filename: executable output file name
 */
static void build_cmd(int type, char *source, char *filename)
{
	char *gcc;

	/* Build command syntax components */
	if(type == Cpp)
	{
		gcc = "g++ ";
	}

	else
	{
		gcc = "gcc ";
	}

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


/* Describe: This function is used to get all arguments that have to passing to the target
 * @argc: numbers of arguments
 * @exe: base execute command depend on language
 * @argv: arguments
 */
static void arg_cml(int argc, char *exe, char *argv[])
{
	int len_exe = strlen(exe);
	int len_cmd = 0;
	int arg[argc];
	char *cmd;

	for(int i=0; i<argc; i++)
	{
		arg[i] = strlen(argv[i]);
	}

	for(int j=1; j<argc; j++)
	{
		len_cmd += arg[j];
	}

	len_cmd += len_exe + (argc-2);
	cmd = malloc(len_cmd);
	strcpy(cmd, exe);
	
	for(int k=2; k<argc; k++)
	{
		strcat(cmd, " ");
		strcat(cmd, argv[k]);
	}
	
	// printf("%s\n", cmd);
	system(cmd);	// execute command
	free(cmd);
}


/* Describe: This function is used to execute the executable file
 * following the according to the type of source file language
 * @type: type of source file language
 * @filename: The executable file input
 */
static void file_exect(int type, int argc, char *arg[])
{
	/* Base execute command */
	char *ec = "./";				// Base command for execute C
	char *py = "python ";			// Base command for python execute
	char *exe;
	int len_exe;
	int len_filename;
	
	char *exe_file;
	
	switch(type)
	{
		case Bash:
			len_exe = strlen(ec);
			exe = ec;
			break;
			
		case Cpp:
		case C:
			exe_file = strcut(type, arg[1]);
			build_cmd(type, arg[1], exe_file);
			len_exe = strlen(ec);
			exe = ec;
			break;
		
		case Python:
			len_exe = strlen(py);
			exe = py;
			break;
	}
	
	/* Merge command component */
	if(type == C || type == Cpp)
	{
		len_filename = strlen(exe_file);
		int len_cmd = len_exe + len_filename;
		char cmd[len_cmd];
		strcpy(cmd, exe);
		strcat(cmd, exe_file);
		arg_cml(argc, cmd, arg);
		exe_remove(exe_file);
	}
	
	else
	{
		len_filename = strlen(arg[1]);
		int len_cmd = len_exe + len_filename;
		char cmd[len_cmd];
		strcpy(cmd, exe);
		strcat(cmd, arg[1]);
		arg_cml(argc, cmd, arg);
	}
}


int main(int argc, char *argv[])
{
	int type = exe_dect(argv[1]);
	file_exect(type, argc, argv);
		
	return 0;
}
