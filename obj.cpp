/*
 * obj.cpp
 * This is an open-source program that help quick execute source file
 * with just only one command.
 * You can clone, uses, modify and distribute it.
 * 
 * Copyright: Binh-Thanh Mai Nguyen (binhmainguyen193@gmail.com).
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;

#include "run.h"



/* Describe: This function is used to delete executable file
 * @filename: executable output file name  
 */
void C_language::exe_remove(char *filename)
{
	const char *rm = "rm -rf ";			  // Base command for remove executable file
	
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


/*
 * Describe: This function is used to generating
 * build command of C code and execute generated command
 * @Source: source file input
 * @filename: executable output file name
 */
void C_language::build_cmd(int type, char *source, char *filename)
{
	const char *gcc;

	/* Build command syntax components */
	if(type == Cpp)
	{
        gcc = "g++ ";
	}

	else
	{
        gcc = "gcc ";
	}

	const char *obj = " -o ";
	
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

/*
* Describe: This function is used to cut (*.c) extention to get only filename
* @source: source file input
*/
char* C_language::strcut(int type, char *source)
{
	int length = strlen(source);
	char *filename;
	
	/* Execute to split file exetention "*.c" */
	switch(type)
	{
		case C:
			filename = new char[length - 2];
			for(int i=0; i<(length-2); i++)
			{
				filename[i] = source[i];
			}
			break;
		
		case Cpp:
			filename = new char[length - 2];
			for(int i=0; i<(length-4); i++)
			{
				filename[i] = source[i];
			}
			break;
	}
	return filename;
}

void C_language::file_exect(int type, int argc, char *arg[])
{
	const char *ec = "./";				// Base command for execute C
	// char *exe, 
	char *exe_file;
	int len_exe, len_filename, len_cmd;

	exe_file = strcut(type, arg[1]);
	build_cmd(type, arg[1], exe_file);
	len_exe = strlen(ec);
	// exe = ec;

	len_filename = strlen(exe_file);
	len_cmd = len_exe + len_filename;
	char cmd[len_cmd];
	strcpy(cmd, ec);
	strcat(cmd, exe_file);
	arg_cml(argc, cmd, arg);
	exe_remove(exe_file);	
}


void Py::file_exect(int argc, char *arg[])
{
	const char *exe = "python ";			// Base command for python execute
	char *exe_file;
	int len_exe, len_filename, len_cmd;

	len_exe = strlen(exe);
	len_filename = strlen(arg[1]);
	len_cmd = len_exe + len_filename;
	char cmd[len_cmd];
	strcpy(cmd, exe);
	strcat(cmd, arg[1]);
	arg_cml(argc, cmd, arg);
}



void ShBash::file_exect(int argc, char *arg[])
{
	const char *exe = "./";				// Base command for execute C
	char *exe_file;
	int len_exe, len_filename, len_cmd;

	len_exe = strlen(exe);
	len_filename = strlen(arg[1]);
	len_cmd = len_exe + len_filename;
	char cmd[len_cmd];
	strcpy(cmd, exe);
	strcat(cmd, arg[1]);
	arg_cml(argc, cmd, arg);
}

/* Describe: This function is used to get all arguments that have to passing to the target
 * @argc: numbers of arguments
 * @exe: base execute command depend on language
 * @argv: arguments
 */
void Executable::arg_cml(int argc, char *exe, char *argv[])
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
	cmd = new char(len_cmd);
	strcpy(cmd, exe);
	
	for(int k=2; k<argc; k++)
	{
		strcat(cmd, " ");
		strcat(cmd, argv[k]);
	}
	
	// printf("%s\n", cmd);
	system(cmd);	// execute command
	delete(cmd);
}