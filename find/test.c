#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
void sort(int values[], int n);
int main (void)
{
    int apple[6];
    for (int i = 0; i < 7; i++)
    {
        apple[i] = GetInt();
    }
    sort (apple, 6);
    for (int i = 0; i < 7; i++)
    {    printf("#%d\n", apple[i]); 
}
}

void sort(int values[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        int j = i;
        int element = values[j+1];
        int element_pos = j + 1;
        while (element < values[j] && j >= 0)
        {
            //swap
            int temp = values[j];
            values[j] = element;
            values[element_pos] = temp;
            j--;
            element_pos--;
        }
    };
    }
