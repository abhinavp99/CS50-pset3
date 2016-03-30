/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (value >= 0)        
    {
        for (int i = 0; i < n; i++)
            {
                if (values[i] == value)
                {
                    return true;
                }
            
            }
    }
   return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min =  values[i];
        int position_min = i;
        for (int j = i +1; j < n; j++)
        {
            if (min > values[j])
            {
                min = values[j];
                position_min = j;
            }
        }
        //swap
        int temp = values[i];
        values[i] = min;
        values[position_min] = temp; 
    }
}

