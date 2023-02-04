// =========================================================================
// File: parallel.c
// =========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// global vars
#define BUFFSIZE 255
char input[BUFFSIZE];

// function prototypes
int parseInput(int in_argc, char *in_argv[], int *in_N, char* in_shell);
int validate_N(const char* in_arg);
int validate_option(const char* in_arg);
void get_shell(char* in_shell);



// ==== main ===============================================================
//
// =========================================================================
int main(int argc, char *argv[])
{
  int N;
  int status_counter = 0;
  int result = 0;
  int N_counter = 0;
  int pid = -1;
  time_t begin = time(NULL);
  char* shell_name = (char*)malloc(BUFFSIZE * sizeof(char));
  
  result = parseInput(argc, argv, &N, shell_name);

  // these are entered based on a return value from the input parse
  if(!result)
    {
      printf("You didn't do something correctly.  Do not pass go, do not collect $200.\n");
      free(shell_name);
      return -1;
    }
  else if(1 == result)
    {
      N = get_nprocs();
      strcpy(shell_name, getenv("SHELL"));
    }
  else if(2 == result)
    {
      if(0 == N)
	N = get_nprocs();
      strcpy(shell_name, getenv("SHELL"));
    }
  else if(3 == result)
    {
      N = get_nprocs();
      strcpy(shell_name, argv[2]);
    }
  else if(4 == result)
    {
      if(0 == N)
	N = get_nprocs();
      strcpy(shell_name, argv[2]);
    }
  
  if(0 < result)
    {
      while(fgets(input, BUFFSIZE, stdin))
	{
	  if(N > N_counter)
	    {
	      N_counter++;
	      pid = fork();
	    }
	  if(0 == pid) // child
	    {
	      execl(shell_name, "sh", "-c", input, NULL);
	      exit(0);
	    }
	  if(0 < pid) // parent
	    {
	      if(N <= N_counter)
		{
		  int status = 0;
		  wait(&status);
		  if(0 != status)
		      status_counter++;
		  N_counter--;
		}
	    }
	}
    }

  // reap children
  int status = 0;
  while(0 < wait(&status))
    if(0 != status)
      status_counter++;

  // get the current time
  time_t end = time(NULL);

  // free any dynamically allocated memory
  free(shell_name);

  // return the exit status value
  return status_counter;
} // end of "main"



// ==== parseInput =========================================================
//
// =========================================================================
int parseInput(int in_argc, char *in_argv[], int *in_N, char* in_shell)
{
  int is_valid = 0;
  switch(in_argc)
    {
      // ./parallel
    case 1:
      is_valid = 1;
      break;
      // ./parallel N
    case 2:
      if(validate_N(in_argv[1]))
	{
	  // if this returns 0, we need to call the processor function in main
	  *in_N = atoi(in_argv[1]);
	  is_valid = 2;
	}
      else
	{
	  printf("Invalid input for N. Exiting\n");
	  return 0;
	}
      break;
      // ./parallel [-s SHELL]
    case 3:
      if(validate_option(in_argv[1]))
	is_valid = 3;
      break;
      // ./parallel [-s SHELL] N
    case 4:
      if(validate_N(in_argv[3]))
	{
	  *in_N = atoi(in_argv[3]);
	  if(validate_option(in_argv[1]))
	    is_valid = 4;
	}
      break;
    default:
      printf("Too many arguments. What in jumpin jupiter are you doing!?\n");
      break;
    }

  if(is_valid)
    {
      return is_valid;
    }
  else
    {
      return 0;
    }
} // end of "parseInput"



// ==== validate_N =========================================================
//
// =========================================================================
int validate_N(const char* in_arg)
{
  int not_valid = 0;
  int len = strlen(in_arg);

  for(int i = 0; i < len; i++)
    {
      if(!(in_arg[i] >= '0' && in_arg[i] <= '9'))
	{
	  not_valid = 1;
	  break;
	}
    }

  if(not_valid)
    {
      return 0;
    }
  else
    {
      return 1;
    }
} // end of "validate_N"



// ==== validate_option ====================================================
//
// =========================================================================
int validate_option(const char* in_arg)
{
  int not_valid = 0;
  if( in_arg[0] != '-')
    not_valid =1;

  if(strlen(in_arg) != 2)
      not_valid =1;

  if(in_arg[1] != 's')
    not_valid =1;

  if(not_valid)
    {
      return 0;
    }
  else
    {
      return 1;
    }
} // end of "validate_option"



// ==== get_shell ==========================================================
//
// =========================================================================
void get_shell(char* in_shell)
{
  strcpy(in_shell, getenv("SHELL"));
} // end of "get_shell"
