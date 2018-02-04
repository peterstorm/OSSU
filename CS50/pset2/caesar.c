#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// main program with commandline arguments
int main(int argc, string argv[]) 
{
    //we only want two commandline arguments (execute program and key)
    if(argc == 2)
    {
        // convert key from string to int
        int key = atoi(argv[1]);
        // ask user for a string to cipher
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        // iterate over all the characters in the string
        for(int i = 0, n = strlen(plaintext); i < n; i++)
        {
            // check if character is alphabetic character
            if(isalpha(plaintext[i]))
            {
                // check up character is capital, and convert to cipher
                if(isupper(plaintext[i]))
                {
                    int upperAlpha = (plaintext[i] + key - 'A') % 26;
                    int upperCypher = upperAlpha + 'A';
                    printf("%c",upperCypher);
                //check if character is lowercase and convert to cipher
                }else if(islower(plaintext[i]))
                {
                    int lowerAlpha = (plaintext[i] + key - 'a') % 26;
                    int lowerCypher = lowerAlpha + 'a';
                    printf("%c",lowerCypher);
                }
            // if character is not alphabetic print untouched - like spaces and numbers
            }else
            {
                printf("%c", plaintext[i]);
            }
            
        }
   } else
    {
       printf("Please only use a positive integer for your commandline argument!\n");
       return 1;
    }
        
    printf("\n");
    return 0;
}
