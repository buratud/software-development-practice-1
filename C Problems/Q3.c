#include <stdio.h>
#include <string.h>
//-----------------------------------------------------------
// str is an array of chars passed as the argument to the function.
//-----------------------------------------------------------
int count_zeros(const char *str)
{
    int size = strlen(str);
    int zCount = 0;
    for (int i = 0; i < size; i++)
    {
        if(*(str + i) != '0' && *(str + i) != '1'){
            return -1;
        }
        if (*(str + i) == '0')
        {
            zCount++;
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