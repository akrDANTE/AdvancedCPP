#include<stdio.h>
#include"assignment13.h"

void print_array(int arr[], int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}
