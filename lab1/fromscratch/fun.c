#include <stdio.h>

int main(int argc, char** argv)
{
    char* first_arg; 
    char* second_arg; 

    /* this checks the number of arguments passed in */
    if (argc != 3) {
        printf("usage: %s <arg1> <arg2>\n", argv[0]);
        return 0;
    }

    first_arg = argv[1];
    second_arg = argv[2];

    printf("My program was given two arguments: %s %s\n",
           first_arg, second_arg);

    return 0;

}
