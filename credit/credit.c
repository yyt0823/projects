#include <stdio.h>
#include <cs50.h>
bool checksum(long int);
void company(long int);
int main(void)
{
    long int CardNumber;
    do
    {
        CardNumber = get_long("Number: ");
    }
    while (CardNumber == false);
    bool checkone = checksum(CardNumber);
    if (checkone)
    {
        company(CardNumber);
    }
    else
    {
        printf("INVALID\n");
    }
}


//verification of card validation
bool checksum(long int number)
{
    long int CardLimit = 100000000000000000;
    int sum = 0;
    //every other digit sum
    for (long int i = 100; i < CardLimit; i *= 100)
    {
        int current = ((number % i) / (i / 10)) * 2;
        if (current >= 10)
        {
            current = (current % 10) + (current / 10);
        }
        sum += current;
    }

    //sum of digits that werent * 2
    for (long int i = 10; i < CardLimit; i *= 100)
    {
        int original = ((number % i) / (i / 10));
        sum += original;
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//distinguish card company
void company(long int cardnum)
{
    if ((cardnum >= 340000000000000 && cardnum < 350000000000000) || (cardnum >= 370000000000000 && cardnum < 380000000000000))
    {
        printf("AMEX\n");
    }
    else if (cardnum >= 5100000000000000 && cardnum  < 5600000000000000)
    {
        printf("MASTERCARD\n");
    }
    else if ((cardnum >= 4000000000000 && cardnum  < 5000000000000) || (cardnum >= 4000000000000000 && cardnum  < 5000000000000000))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}