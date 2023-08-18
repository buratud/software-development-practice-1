# C Problem

## Problem 1 solution

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    // This is declaration of a character array. Characters ending with null terminator can be used as a string.
    char data[] = {'A', 'B', 'c', '\0'};
    // p is a pointer variable, which points to the same address as data.
    char *p = data;
    // This will print the memory address the p point to, in this case 0x7fcb6ca200
    printf("p = %p\n", p);
    // This will print the memory address of the data, in this case 0x7fcb6ca200. The same as p.
    printf("data = %p\n", data);
    // This will print the pointer to first element of the data array, which is 0x7fcb6ca200.
    printf("&data[0] = %p\n", &data[0]);
    // This will print the pointer to second element of the data array, which is 0x7fcb6ca201.
    printf("&data[1] = %p\n", &data[1]);
    // This will print the pointer to third element of the data array, which is 0x7fcb6ca202.
    printf("&data[2] = %p\n", &data[2]);
    // This will print the value of the first element of the data array, which is A.
    printf("data[0] = %c\n", *&data[0]);
    // This will print the value of the second element of the data array, which is B.
    printf("data[1] = %c\n", *&data[1]);
    // This will print the value of the third element of the data array, which is c.
    printf("data[2] = %c\n", *(data + 2));
    // This will print the value of the third element of the data array, which is c.
    printf("data[2] = %c\n", (&p[1] + 1)[0]);
    // This will print the string value from the data array.
    printf("data = %s\n", data);
    // This will print the size of the data array. It will include the null terminator.
    printf("sizeof(data) = %lu bytes\n", sizeof(data));
    // This will print the length of the string. Which is 3. It will not include the null terminator.
    printf("strlen(data) = %lu bytes\n", strlen(data));
    return 0;
}
```

## Problem 2 solution

```c
// The concept is to swap the first and last element while moving both pointers until they have reached the center

void reverse_array(int *array, int num_elements) {
    for (int i = 0; i < num_elements / 2; i++) {
        // This variable is to locate the last element of the array
        int j = num_elements - i - 1;
        // keep is a temporary variable, which will contain an element used for the swapping process
        int keep = *(array + j);
        *(array + j) = *(array + i);
        *(array + i) = keep;
    }
}
```

## Problem 3 solution

## Problem 4 solution
