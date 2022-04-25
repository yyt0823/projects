#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string username = get_string("What is ur name?\n");
    printf("hello, %s\n", username);
}