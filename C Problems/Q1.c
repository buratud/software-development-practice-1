#include <stdio.h>
#include <string.h>

int main(void) {
    char data[] = {'A', 'B', 'c', '\0'};
    // p is a pointer variable, which points to the same address as data.
    char *p = data;
    printf( "p = %p\n", p );
    printf( "data = %p\n", data );
    // This will print the memory address 0x7fcb6ca200
    printf( "&data[0] = %p\n", &data[0] );
    printf( "&data[1] = %p\n", &data[1] );
    printf( "&data[2] = %p\n", &data[2] );
    printf( "data[0] = %c\n", *&data[0] );
    printf( "data[1] = %c\n", *&data[1] );
    printf( "data[2] = %c\n", *(data+2) );
    printf( "data[2] = %c\n", (&p[1]+1)[0] );
    printf( "data = %s\n", data );
    printf( "sizeof(data) = %lu bytes\n", sizeof(data) );
    printf( "strlen(data) = %lu bytes\n", strlen(data) );
    return 0;
}