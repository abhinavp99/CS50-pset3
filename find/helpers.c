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
    int lower = 0;
    int upper = n;
    while (lower <= upper)
    {
        int midpoint = (lower + upper) / 2;
        if (value > values[midpoint])
        {
            lower = midpoint + 1;
        }
        else if (value < values[midpoint])
        {
            upper = midpoint - 1;
        }
        else if (value == values[midpoint])
        {
            return true;
        }              
    }
    return false;  
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    //optimizing number
    int k = 0;
    int counter = 0; 
    do
    {
        counter = 0;
        for (int i = 0; i < n-1-k; i++)
        {
            if(values[i] > values[i+1])
            {
                int temp = values[i+1];
                values[i+1] = values[i];
                values[i] = temp;
                counter++;
            }
        }
        k++;
    }
    while (counter > 0);
    return;
};


