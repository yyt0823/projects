#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
int CountLetter(string);
int CountWord(string);
int CountSentence(string);

int main(void)
{
    //take input
    string input = get_string("TEXT: ");
    float letters = CountLetter(input);
    float words = CountWord(input);
    float sentences = CountSentence(input);
    float index = 0.0588 * (letters / words) * 100 - 0.296 * (sentences / words) * 100 - 15.8;
    int final = round(index);
    //grade before 1  and 16+
    printf("%f, %f, %f", letters, words, sentences);
    if (final <= 1)
    {
        printf("Text: %s\nBefore Grade 1\n", input);
    }
    else if (final >= 16)
    {
        printf("Text: %s\nGrade 16+\n", input);
    }
    else
    {
        printf("Text: %s\nGrade %i\n", input, final);
        printf("%f, %f, %f", letters, words, sentences);
    }






}

//computes letters

int CountLetter(string text)
{
    int LetterCount = 0;
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            LetterCount++;
        }
    }
    return LetterCount;
}

//computes Word

int CountWord(string text)
{
    int WordCount = 0;
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            WordCount++;
        }
    }
    return WordCount;
}

//computes sentence

int CountSentence(string text)
{
    int SentenceCount = 0;
    int length = strlen(text);
    for (int i = 0; i <= length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            SentenceCount++;
        }
    }
    return SentenceCount;
}