#include <stdio.h>
#include <string.h>
// str is an array of chars passed as the argument to the function.
int detect_pattern(const char *str)
{
    int length = strlen(str);
    int state = 0;
    for (int i = 0; i < length; i++)
    {
        if (*str == '1')
        {
            if (state == 0)
            {
                state = 1;
            }
            else if (state == 2)
            {
                return 1;
            }
        }
        else if (*str == '0' && state != 0)
        {
            state = 2;
        }
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