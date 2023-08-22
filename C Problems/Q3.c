#include <stdio.h>
#include <string.h>
//-----------------------------------------------------------
// str is an array of chars passed as the argument to the function.
//-----------------------------------------------------------
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

int main(void)
{
    char *arr[] = {
        "", "0", "1", "00", "0110", "01001110111011"};
    // compute the number of strings in the array 'arr'
    int n = sizeof(arr) / sizeof(char *);
    printf("n = %d\n", n);
    for (int i = 0; i < n; i++)
    {
        char *str = arr[i];
        int result = count_zeros(str);
        if (result == -1)
        {
            printf("Invalid binary string: %s\n", str);
        }
        else
        {
            int len = strlen(str);
            printf("#0 = %d, #1 = %d, s='%s'\n",
                   result, len - result, str);
        }
    }
    return 0;
}