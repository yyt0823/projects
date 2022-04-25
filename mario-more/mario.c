#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int UserInput;
    do
    {
        UserInput = get_int("Height:  ");
    }
    while (1 > UserInput || UserInput > 8);


    //create layers
    for (int i = 0; i < UserInput; i++)
    {
        //create white-spaces
        for (int x = 1; x < UserInput - i; x++)
        {
            printf(" ");
        }
        //create left # block
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //create middle white-spaces
        printf("  ");
        //create right # block
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //create new line
        printf("\n");

    }











}
