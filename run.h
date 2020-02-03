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

/* Language ID definition */
#define C 		1
#define Python 	2
#define Bash 	3
#define Cpp     4

/* 
 * Describe: This function is used to detecting source file format
 * @source: the source input
 */
static int exe_dect(char *source);

/*
 * Describe: This function is used to cut (*.c) extention to get only filename
 * @source: source file input
 */
static char *strcut(int type, char *source);

/*
 * Describe: This function is used to generating
 * build command of C code and execute generated command
 * @Source: source file input
 * @filename: executable output file name
 */
static void build_cmd(int type, char *source, char *filename);

/* Describe: This function is used to delete executable file
 * @filename: executable output file name  
 */
static void exe_remove(char *filename);

/* Describe: This function is used to get all arguments that have to passing to the target
 * @argc: numbers of arguments
 * @exe: base execute command depend on language
 * @argv: arguments
 */
static void arg_cml(int argc, char *exe, char *argv[]);

/* Describe: This function is used to execute the executable file
 * following the according to the type of source file language
 * @type: type of source file language
 * @filename: The executable file input
 */
static void file_exect(int type, int argc, char *arg[]);
