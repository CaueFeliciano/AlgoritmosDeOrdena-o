#include <stdio.h>
#include <time.h>

// 1 - Selection Sort
void selectionSort(int *v)
{
    int i, j, min, aux;
    for (i = 0; i < 9; i++)
    {
        min = i;
        for (j = i + 1; j < 10; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}