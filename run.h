/*
 * run.h
 * This is an open-source program that help quick execute source file
 * with just only one command.
 * You can clone, uses, modify and distribute it.
 * 
 * Copyright: Binh-Thanh Mai Nguyen (binhmainguyen193@gmail.com).
 */

/* Language ID definition */
#define C 		1
#define Python 	2
#define Bash 	3
#define Cpp     4


class Executable
{
	protected:
		void arg_cml(int argc, char *exe, char *argv[]);
		virtual void file_exect(){};
};


class C_language: public Executable
{
	private:
		/* Describe: This function is used to delete executable file
 		 * @filename: executable output file name  
 		 */
		void exe_remove(char *filename);
		/*
 		 * Describe: This function is used to generating
 		 * build command of C code and execute generated command
 		 * @Source: source file input
 		 * @filename: executable output file name
 		 */
		void build_cmd(int type, char *source, char *filename);

		/*
 		* Describe: This function is used to cut (*.c) extention to get only filename
 		* @source: source file input
 		*/
		char *strcut(int type, char *source);

	public:
		void file_exect(int type, int argc, char *arg[]);
};


class Py: public Executable
{
	public:
		void file_exect(int argc, char *arg[]);
};


class ShBash: public Py
{
	public:
		void file_exect(int argc, char *arg[]);
};