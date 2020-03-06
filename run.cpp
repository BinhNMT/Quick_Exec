/*
 * run.cpp
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


/* 
 * Describe: This function is used to detecting source file format
 * @source: the source input
 */
static int detect_language(char *source)
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
	
	buff = new char(count);
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
		delete(buff);
		return ret;
}


int main(int argc, char *argv[])
{
	// Executable *lang_exe;
	C_language c_lang;
	Py py_lang;
	ShBash shbsh_lang;

	int type = detect_language(argv[1]);
	switch(type)
	{
		case Cpp:
		case C:
			c_lang.file_exect(type, argc, argv);
			break;
		
		case Python:
			py_lang.file_exect(argc, argv);
			break;

		case Bash:
			shbsh_lang.file_exect(argc, argv);
			break;
		
		default:
			cout << "Not supported\n";
	}
		
	return 0;
}
