#include <stdio.h>
//-----------------------------------------------------------
// Function arguments:
// array - an array of integers
// num_elements - the number of elements (integers) in the array
//-----------------------------------------------------------
void reverse_array(int *array, int num_elements)
{
    for (int i = 0; i < num_elements / 2; i++)
    {
        int j = num_elements - i - 1;
        int keep = *(array + j);
        *(array + j) = *(array + i);
        *(array + i) = keep;
    }
}
void print_array(int *array, int num_elements)
{
    for (int i = 0; i < num_elements; i++)
    {
        printf("%d%s", array[i], (i == num_elements - 1) ? "\n" : ",");
    }
}
int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a) / sizeof(int);
    reverse_array(a, n);
    print_array(a, n);
    reverse_array(&a[2], n - 2);
    print_array(a, n);
    return 0;
}