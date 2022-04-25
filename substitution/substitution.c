#include <stdio.h>
#include <cs50.h>
#include <string.h>

int validation(string);
void encrypt(string, string);


int main(int argc, string argv[])
{
    //cla
    string key = argv[1];
    //exit status
    if (key)
    {
        if (validation(key) == 1)
        {
            return 1;
        }
    }
    else
    {
       printf("Usage: ./substitution key\n");
       return 1;
    }
    //prompt
    string input = get_string("plaintext:  ");
    //encrypt
    encrypt(input, key);
    printf("\n");
    return 0;



}



//ciphertext
void encrypt(string input, string key)
{
    int list[26];
    int difference;
    int length = strlen(input);
    for (int i = 0; i < 26; i++)
    {
        if ('a' <= key[i] && key[i] <= 'z')
        {
            difference = key[i] - ('a' + i);
        }
        else if ('A' <= key[i] && key[i] <= 'Z')
        {
            difference = key[i] - ('A' + i);
        }
        else
        {
            difference = 0;
        }
        list[i] = difference;
    }
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        int output = 0;
        if ('a' <= input[i] && input[i] <= 'z')
        {
            output = input[i] + list[input[i] - 97];
        }
        else if ('A' <= input[i] && input[i] <= 'Z')
        {
            output = input[i] + list[input[i] - 65];
        }
        else
        {
            output = input[i];
        }
        printf("%c", output);
    }
}



//validate key
int validation(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        if ('A' > key[i] || key[i] > 'z' || ('Z' < key[i] && key[i] < 'a'))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        if (length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j])
            {
                printf("No duplicate characters.\n");
                return 1;
            }
        }
    }
    return 0;
}