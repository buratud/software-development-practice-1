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
