#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int letter(char let)make key letter
{
    if(isupper(let))
        return let - 'A';
    else
        return let -'a';
}
int main(int argc, string argv[])
{
    if(argc != 2) 
    {
        printf("Input your alphabetic key\n");
        return 1;
    }
    string key = argv[1];
    for(int i = 0, n = strlen(key); i < n; i++)// test key is word
    if(!isalpha(key[i]))
    {
    printf("input alphabetic key\n");
    return 1;
    }
    printf("plaintext: ");

    string text = get_string();// input text
   
    if(text != NULL)
    {
        printf("ciphertext: ");
         int k = strlen(key);// lenght of key
        int j = 0;// index of key
        for(int i = 0, n = strlen(text); i < n; i++)
        {
           if(isalpha(text[i]))//cipher letter
           {
                 if(isupper(text[i]))
                printf("%c", (((text[i] - 'A') + letter(key[j % k])) % 26) + 'A');
               else
                 printf("%c", (((text[i] - 'a') + letter(key[j % k])) % 26) + 'a');
                 j++;
            }
            else
                printf("%c", text[i]);
        }
        printf("\n");   
    }
    return 0;
}
