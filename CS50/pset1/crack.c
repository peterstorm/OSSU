#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// define limits for salt, password 
// and the number of characters we iterate over
#define SALT_SIZE               2
#define MAX_PASS_LENGTH         5
#define MAX_NUM_CHARACTERS      52

// define functions
void getSalt(char salt[], string hash);
void bruteAttack(char brutePass[], string hash);
void bruteForce(
    string hash, char brutePass[], char pass[], int pos, int maxLength, 
    char passCharacters[]);


int main(int argc, string argv[])
{
    // ensure that user has provided commandline argument
    if(argc == 2)
    {
        string hash = argv[1];
        char brutePass[MAX_PASS_LENGTH + 1] = "";
        bruteAttack(brutePass, hash);
        printf("%s\n", brutePass);
    }
    else
    {
        // if user has not provied the correct number of 
        // commandline arguments, print error
        printf("Please provide hash as a commandline argument\n");
        return 1;
    }
    
}

// function to get the 'salt' (two first characters in hash).
void getSalt(char salt[], string hash)
{
    salt[SALT_SIZE] = '\0';
    strncpy(salt, hash, SALT_SIZE);
}

void bruteAttack(char brutePass[], string hash)
{
    // generate character pool, comprised of the alphabet only
    int i = 'A';
    int j = 0;
    char passCharacters[MAX_NUM_CHARACTERS];
    while(i <= 'z')
    {
        if(isalpha(i))
        {
            passCharacters[j] = i;
            j++;
        }
        i++;
    }
    // generate container for the generated passwords
    // + 1 is to fit null terminator, if the algorithm goes to 5 characters.
    char pass[MAX_PASS_LENGTH + 1];
    
    for (int length = 1; length <= MAX_PASS_LENGTH; length++)
    {
        // set the last element in the array to null, so we can do string things with it.
        pass[length] = '\0';
        
        // call the bruteForce function for each password length, with an index position of 0, to start with the first character
        bruteForce(hash, brutePass, pass, 0, length, passCharacters);
        
        // break out of loop, if we find a password match
        if (strlen(brutePass) > 0)
        {
            break;
        }
    }
    
    return;
}

void bruteForce(
    string hash, char brutePass[], char pass[], int pos, int maxLength, 
    char passCharacters[])
{
    string passHash;

    // get salt from hash
    char salt[3];
    getSalt(salt, hash);

    // iterate through every character we have defined for a possible password
    for (int i = 0; i < MAX_NUM_CHARACTERS; i++)
    {
        // set position to iterate over all possible characters
        pass[pos] = passCharacters[i];

        // check every generated string of the specified length, by encrypting and comparing hashes
        if (pos == maxLength - 1)
        {
            // encrypt with the salt hash
            passHash = crypt(pass, salt);
            // if the hashes match, copy the found password, break out of function, verify in bruteAttack
            if (strcmp(passHash, hash) == 0)
            {
                strcpy(brutePass, pass);
                break;
            }
        }
        else
        {
            // recursively call bruteForce, incrementing the word position
            // where we iterate through every character in the new position
            // and because it is recursive, it does this with all the possible
            // characters in the former position too - woo, recursion!
            bruteForce(hash, brutePass, pass, pos + 1, maxLength, passCharacters);
        }
    }
}