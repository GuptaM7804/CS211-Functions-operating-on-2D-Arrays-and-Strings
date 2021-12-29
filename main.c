#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
/* #include "prog3.h" */



/**
* 
*  Function "stubs" for Assignment 3 exercises.
*
*  See prog3.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char** alloc_square_mtx(int n)
{
    char** darr = (char**) malloc (n * sizeof(char*)); //size n for the number of elements

    for (int i = 0; i < n; i++)
        darr[i] = (char*) malloc (n * sizeof(char)); //size n for each element in array
    
    return darr;
}

void free_square_mtx(char **m, int n)
{
    for(int i=0;i<n;i++)
        free(m[i]); //free each element
    
    free(m); //free the array
}

void pop_mtx_alpha(char **m, int n)
{
    srand(time(NULL));
    char l_case[26] = {'a', 'b', 'c', 'd', 'e', 
    'f', 'g', 'h', 'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'q', 'r', 's', 
    't', 'u', 'v', 'w', 'x', 'y', 'z'}; // all the letters

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
            m[i][j] = l_case[rand() % 26]; // random letter for each element in each element array
    }
}


void display_mtx(char **m, int n)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n-1; j++)
            printf("%c ", m[i][j]); // print each row elements
        
        printf("%c\n", m[i][n-1]); // add 'newline' after last element in row
    }
}

void swap_rows(char **m, int n, int r1, int r2)
{
    if (r1 >= n || r2 >= n || r1 < 0 || r2 < 0)
    {}
    else
    {
        char temp[n];
        
        for(int i=0; i<n; i++)
        {
            temp[i] = m[r1][i]; // temp = 1st row to be swapped
            m[r1][i] = m[r2][i]; // 1st row = 2nd row
            m[r2][i] = temp[i]; // 2nd row = temp == 1st row
        }
    }
}

void swap_cols(char **m, int n, int c1, int c2)
{
    if (c1 >= n || c2 >= n || c1 < 0 || c2 < 0)
    {}
    else
    {
        char temp[n];
        
        for(int i=0; i<n; i++)
        {
            temp[i] = m[i][c1]; // same as above but for columns
            m[i][c1] = m[i][c2];
            m[i][c2] = temp[i];
        }
    }
}


void rotate_right(char **m, int n)
{
    char temp[n][n];
    
    for (int i = 0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            temp[i][j] = m[n-j-1][i]; // temp's first colum = bottom row
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            m[i][j] = temp[i][j]; // copy temp into m
    }
}


void floating_boulders(char **m, int n, int nb)
{
    srand(time(NULL));
    
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
            m[i][j] = '.'; // make everything '.'
    }
    
    for(int i=0; i<nb; i++)
        m[rand()%n][rand()%n] = '#'; // get random position for '#'
}


void mountains(char **m, int n)
{
    srand(time(NULL));
    
    for(int i=0; i<n; i++)
    {
        int col = rand() % n; // random number for boulders, per each column
        int air = n-col; // number of air needed in that column
        for(int j=0; j<air; j++)
            m[j][i] = '.'; // add air in that column
        for(int j=air; j<n; j++)
            m[j][i] = '#'; // then add boulders in that column
    }
}


void sink(char **m, int n)
{
    for(int i = 0; i<n; i++)
    {
        for(int j=n-1; j>0; j--)
        {
            if(m[j][i] != '.') // checks if that row has anything other than air
            {
                m[j][i] = m[j - 1][i]; // pushes the 'something' down if it is not air
            }
            if(j==1)
                m[j-1][i] = '.'; // turns the top row into air
        }
    }
}


void gravity(char **m, int n)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = (n - 1); j >= 0; j--)
        {
            if(m[j][i] == '.') // if air, then...
            {
                for(int z = (j - 1); z >= 0; z--) // triple nested loop to account for spaces of more than 1
                {
                    if(m[z][i] != '.') // if not air, then...
                    {
                        m[j][i] = m[z][i]; // swap the air for the boulder/other object 
                        m[z][i] = '.'; // make that position an air char
                        break; // break out and loop again
                    }
                }
            }
        }
    }
}




/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s)
{
    int i, j;
    
    for(i=0; s[i] == ' ' || s[i] == '\t'; i++); // increase i for each space
    
	for(j=0; s[i]; i++)
		s[j++] = s[i]; // iterate through j which is now equal to the iterated i
	
	s[j] = '\0'; // add an ending
	
	for(i=0; s[i]!='\0'; i++) //while s[i] is not ending
	{
		if(s[i] != ' ' && s[i] != '\t') // if not space then copy j to i
			j = i;
	}
	
	s[j+1] = '\0'; // add ending
}


int str_search(char *s, char *pattern)
{
    int i = 0, j = 0, len1 = strlen(s), len2 = strlen(pattern); // initialize all ints needed
    if (len1 >= len2) // if they are the same length or if the substring is of less length than the string to be checked
    {
        for (i = len1 - len2; i >= 0; i--) // check from behind the string to front, starting from all possible locations the string can be
        {
            int y_n = 1; // a check for if the substring exists or not
            for (j = 0; j < len2; j++)
            {
                if (s[i + j] != pattern[j]) // if the pattern does not exist, then...
                {
                    y_n = 0; // make check = 0
                    break; // break loop
                }
            }
            if (y_n == 1) // if found
                return i; // return the pos
        }
    return -1;
    }
}





#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main()
{


  // test driver


}


#endif        // DO NOT REMOVE THIS LINE!!!


