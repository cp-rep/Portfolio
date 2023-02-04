#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define SIZE 512

// function prototypes
void filePrint(int in_n, int in_m, char* in_file);
void parseOptions(int *in_n, int *in_m, char* in_arg, int *valid, 
              int *in_caseNum, int *in_m_count, int *in_n_count);
void getOptions(char* in_nBuf, char* in_mBuf, char* in_arg, int* in_n, 
                                          int* in_m, int *in_n_count);



// ==== main ===============================================================
//
// =========================================================================
int main(int argc, char *argv[])
{
  char temp = '-';
  char fileBuf[512];
  char* envVar;
  int caseNum = 2;
  int envCase = 0;
  int isValid = 1;
  int n = 0;
  int m = 0;
  int n_count = 0;
  int m_count = 0;
  int noFileFlag = 0;
  
  // defualt: no file arguments provided set the flag
  if(argc == 1)
    noFileFlag = 1;
  // case 1 and 2
  else if (argv[1][0] == '-')
    {
      // parse the options
      parseOptions(&n, &m, argv[1], &isValid, &caseNum, &m_count, &n_count);

      // check for case 1 and 2 file arguments
      if(argc == 2)
	noFileFlag =1;
    }
  // case 3 with file(s) provided
  else
    {
      // check for env variable
      printf("Env Var Test\n");
      envVar = getenv("EVERY");
      
      // if no environment variable is found, set default values to n and m
      if(envVar == 0)
	{
	  printf("No Env Var defined\n");
	  n = 1;
	  m = 1;
	  caseNum = 3;
	}
      // parse the environment variable
      else
	{
	  printf("Every: %s\n", envVar);
	  parseOptions(&n, &m, envVar, &isValid, &caseNum, &m_count, &n_count);
	  envCase = 1;
	}
    }


  if(!isValid)
    printf("Invalid options entered.\n");
  else
    {
      char nBuf[n_count + 1];
      char mBuf[m_count + 1];
      int i, j;

      // process stadard input      
      if(noFileFlag)
	{
	  printf("No File Found. Input file names: ");
	  char c;
	  for(j = 0;c != '\r' || c != '\n'; j++)
	    {
	      c = getc(stdin);
	      fileBuf[j] = c;
	    } 
	      
	  printf("FileBuf: %s\n", fileBuf);
	}

      // get options and print results based on cases
      switch(caseNum){
      case 1: // -N,M supplied
	printf("Switch 1\n");	
	if(envCase)
	  {
	    printf("Every Case\n");
	    getOptions(nBuf, mBuf, envVar, &n, &m, &n_count);
	    for(i = 1; i < argc; i++)
	      filePrint(n, m, argv[i]);
	  }
	else
	  {
	    printf("-N,M Case\n");
	    getOptions(nBuf, mBuf, argv[1], &n, &m, &n_count);
	    for(i = 2; i < argc; i++)
	      filePrint(n, m, argv[i]);
	  }
	// print the files according to -N,M case
	break;
      case 2: // -N supplied
	printf("Switch 2\n");
	// print the files according to -N case
	if(envCase)
	  {
	    printf("None Case\n");
	    getOptions(nBuf, mBuf, envVar, &n, &m, &n_count);
	    for(i = 1; i < argc; i++)
	      filePrint(n, m, argv[i]);
	  }
	else
	  {
	    printf("-N Case\n");
	    getOptions(nBuf, 0, argv[1], &n, &m, &n_count);
	    for(i = 2; i < argc; i++)
	      filePrint(n, m, argv[i]);
	  }
	//	for(i = 2; i < argc; i++)
	//	  filePrint(n, m, argv[i]);
	break;
      case 3: // none supplied, no $EVERY found
	printf("Switch 3\n");	
	// print the files according to no options case
	for(i = 1; i < argc; i++)
	  filePrint(1, 1, argv[i]);
	break;
      default:
	break;
      }
    }

  return 0;

} // end of "main"



// ==== filePrint ==========================================================
// Description: Simply prints the contents the given file depending on the
//  the N and M values provided.
// =========================================================================
void filePrint(int in_n, int in_m, char* in_file)
{
  char lineBuf[SIZE];
  FILE *fp = fopen(in_file, "r");
  int lineCount;
  int i;

  // check if the file was opened successfully
  if(fp == 0)
    {
      printf("Error -- could not open file. Exiting.\n");
      exit(1);
    }

  for(lineCount = 0; fgets(lineBuf, sizeof(lineBuf), fp); lineCount++)
    {
      if(lineCount % in_n == 0)
	{
	  printf("%s", lineBuf);
	  
	  for(i = 1; i < in_m; i++)
	    {
	      if(fgets(lineBuf, sizeof(lineBuf), fp))
		{
		  lineCount++;
		  printf("%s", lineBuf);
		}
	    }
	}
    }
    
  fclose(fp);
} // end of "filePrint"



// ==== parseOptions =======================================================
// Descripton:
//  Parses the options and defines which case the options fall under
//  while parsing them.
//  Case 1: -N,M
//  Case 2: -N
//
//  Any incorrect input of case options will return an error value.
//  The only input accepted are -(int),(int), or -(int).
// =========================================================================
void parseOptions(int *in_n, int *in_m, char* in_arg, int *valid, 
		          int *in_caseNum, int *in_m_count, int *in_n_count)
{
  if(in_arg[1] < '0' || in_arg[1] > '9')
    *valid = 0;
  else
    {
      // find out if it's case 1 or 2 by scanning for a comma
      int i;
      
      for(i = 1; in_arg[i] != 0; i++)
	{
	  //	  printf("%c", in_arg[i]);
	  // comma found, it's case 1
	  if(in_arg[i] == ',')
	    {
	      // make sure there is a digit after the comma
	      if(in_arg[i+1] < '0' || in_arg[i+1] > '9')
		*valid = 0;
	      else 
		*in_caseNum = 1;
	    }
	}
	      
      // we found a comma, and there is a digit after it -- case 1: -N,M
      if(*in_caseNum == 1 && *valid)
	{
	  printf("Case 1\n");
	  // test for valid input up to the comma
	  for(i = 1; in_arg[i] != ','; i++)
	    {
	      if(in_arg[i] < '0' ||  in_arg[i] > '9')
		*valid = 0;
	      (*in_n_count)++;
	    }
		  
	  i++;
	  // test for valid input after the comma
	  for(; in_arg[i] != 0; i++)
	    {
	      if(in_arg[i] < '0' || in_arg[i] > '9')
		*valid = 0;
	      (*in_m_count)++;
	    }
	}
      // case 2: -N
      else if(*in_caseNum == 2 && *valid)
	{
	  printf("Case 2\n");
	  // test for valid input up to the null
	  for(i = 1; in_arg[i] != 0; i++)
	    {
	      if(in_arg[i] < '0' ||  in_arg[i] > '9')
		*valid = 0;
	      (*in_n_count)++;
	    }
	}
    }  
} // end of "parseOptions"



// ==== getOptions =========================================================
// Description: Gets and converts the string options to integer values
// =========================================================================
void getOptions(char* in_nBuf, char* in_mBuf, char* in_arg, int* in_n, 
                                                 int* in_m, int *in_n_count)
{
  // get N and M
  int i, j;
  
  for(i = 0; i < *in_n_count; i++)
    {
      in_nBuf[i] = in_arg[i+1];
    }
  in_nBuf[i] = 0;

  if(in_mBuf != 0)
    {
      i++;
      for(j = 0; in_arg[i] != 0; i++, j++)
	{
	  in_mBuf[j] = in_arg[i+1];
	}
      in_mBuf[j] = 0;
      *in_m = atoi(in_mBuf);
    }
  *in_n = atoi(in_nBuf);
} // end of "getOptions"
