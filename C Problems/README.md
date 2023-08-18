# C Problem

## Problem 1 solution

```c
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

```c
int count_zeros(const char *str)
{
    // This will get the size of the string
    int size = strlen(str);
    // This is basically a variable to keep the total number of zeros
    int zCount = 0;
    // Iterate through every single character in the string
    for (int i = 0; i < size; i++)
    {
        // If the character is a zero, increment the counter
        if (*(str + i) == '0')
        {
            zCount++;
        }
        // Otherwise, if the character is not a zero, immediately return -1
        else if(*(str + i) != '1'){
            return -1;
        }
    }
    return zCount;
}
```

## Problem 4 solution
This code about to check "Binary is a pattern "10+1"" \
"10+1" means the binary has 1, 0 and 1 followed by sequence

```c
#include <stdio.h>
#include <string.h>
// str is an array of chars passed as the argument to the function.
int detect_pattern(const char *str)
{
    //Get length of string in str variable
    int length = strlen(str);
    //This will contain state of pattern
    int state = 0;
    // Iterate through every character in string
    for (int i = 0; i < length; i++)
    {
        //If character is 1 then check the state
        if (*str == '1')
        {
            //If state is 0, Set state to 1
            if (state == 0)
            {
                state = 1;
            }

            //but, If state is 2, Immediately return 1
            else if (state == 2)
            {
                return 1;
            }
        }
        //In otherhand, If character is 0 and state is not 0, Set the state to 2
        else if (*str == '0' && state != 0)
        {
            state = 2;
        }
        //so, If character is not 1, or character is not 0 and state is 0 at the same time, Reset the state
        else
        {
            state = 0;
        }
        str++;
    }
    return 0;
}
int main(void)
{
    char *test[] = {"", "10", "0100", "011000", "1010", "0111001", "01110001", "011100021"};
    int n = sizeof(test) / sizeof(char *);
    for (int i = 0; i < n; i++)
    {
        char *s = test[i];
        printf("'%s': %d\n", s, detect_pattern(s));
    }
    return 0;
}
```
