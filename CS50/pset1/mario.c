#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declaring variables
    
    int height;
    int row;
    int space;
    int hash;
    
    //asking user for height of pyramid
    
    do {
        printf("This program will print a \"mario\" full pyramid.\n");
        printf("Please input a number between 0 and 23 (23 included).\n");
        printf("This will determine the height of the pyramid.\n");
        printf("Please input number: ");
        height = get_int();
    } while (height < 0 || height > 23);
    
    //printing pyramid
    
    
    for (row = 0; row < height; row++) {
        
        for (space = height - 1; space > row; space--) {
            printf(" ");
        }
        
        for (hash = height - space; hash < height + 1; hash++) {
            printf("#");
        }
        
        printf("  ");

        for (hash = 0; hash < row + 1; hash++) {
            printf("#");
        }
        
        printf("\n");
    }
}