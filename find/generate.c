/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    /* Verifies the command line input to check whether one or two arguments are given
     * If not it prints out proper usage
     */
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    /* Declares an integer with the value of the user's first command line input
     * This integer represents the number of pseudorandom numbers desired
     */
    int n = atoi(argv[1]);

    /* Checks whether the user inputted a seed
     * If so, then it uses srand48 to generate a seed for drand48
     * If not, then it simply tells srand48 not to generate anything
     */
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    /* This runs the for loop once for each number the user requested
     * It prints each number, which are generated through drand48
     */
      
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
