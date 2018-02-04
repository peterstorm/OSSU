#include <stdio.h>
#include <cs50.h>
#include <math.h>
// declare variables
long long ccNumber;
// declare functions for checking creditcard type
int ccType(long long x);
int count(long long x);
int * buildArray(long long x);
int luhn(long long x);
// main program
int main(void)
{
    ccNumber = get_long_long("Please input creditcard number: ");
    luhn(ccNumber);
}
// function to find the credit card type
int ccType(long long x) 
{    
    long long ccLength = count(x) - 2;
    long long findFirstTwo = pow(10,ccLength);
    int firstTwo = (x / findFirstTwo);
    if(firstTwo == 37 && count(x) == 15) 
    {
        printf("AMEX\n");
    } else if((firstTwo == 41 || firstTwo == 40) && count(x) == 16) 
    {
        printf("VISA\n");
    } else if((firstTwo == 55 || firstTwo == 51) && count(x) == 16) 
    {
        printf("MASTERCARD\n");
    } else 
    {
        printf("INVALID\n");
    }   
    return 0;
}
// function to find the number of digits in number
int count(long long x) 
{    
    long long calcCC = x;
    int digits = 0;
    while(calcCC != 0) 
    {
        calcCC /= 10;
        ++digits;
    }
    return digits;
}
// function to build array of numbers
int *buildArray(long long x) 
{
    int nItems = count(x);
    int *array = calloc(nItems,sizeof(int));
    int digit = nItems - 1;
    // create array of creditcard number
    for (int i = 0; i < nItems; i++) 
    {
        long long place = pow(10,digit);
		array[i] = (x / place ) % 10;
	    digit--;
    }
    return array;
}
// function to verify the validity of credit card
int luhn(long long x) 
{
    // first we build an array of every other number, starting from the back and multiply those by two
    int numberOfDigits = count(x);
    int *a = buildArray(x);
	int bSize = numberOfDigits / 2;
	int multiply;
	int b[bSize];
	int j = 0;
	for (int i = numberOfDigits - 2; i > -1; i-=2) 
	{  
	    multiply = a[i] * 2;
	    b[j] = multiply;
	    j++;
	} 
	// then we need to find the sum of the digits, not the numbers (so 14 is not 14, its 5, 1 + 4)
    int doubleSum = 0;
    int singleSum = 0;
	for (int l = 0; l < j; l++) 
	{
	    // we find any numbers in the array that are double digits, and add them together
	    if(count(b[l]) > 1) 
	    { 
	        int digitOne = b[l] % 10;
	        int digitTwo = b[l] / 10;
	        int sumDouble = digitOne + digitTwo;
	        doubleSum = sumDouble + doubleSum;
	        // then we find all the single digit numbers and add them together
	    } else if (count(b[l]) < 2 ) 
	    {
	        int sumSingle = b[l];
	        singleSum = sumSingle + singleSum;
	    }
	}
	// and then we add the two part sums together
	int productSum = singleSum + doubleSum;
	// then we add the numbers of the numbers not multiplied by two
	int addSum = 0;
	for (int k = numberOfDigits - 1; k > -1; k-=2) 
	{
	    int add = a[k];
	    addSum = add + addSum;
	}
	// then we add the sum of multiplied numbers and the sum of the numbers that weren't
	int luhnValue = addSum + productSum;
    // if the value of the two added numbers equal 0, if you take the modulus of 10, it is a valid creditcard number!
	if (luhnValue % 10 == 0) 
	{
	    ccType(ccNumber);
	} else
	{
	    printf("INVALID\n");
	}
    return 0;
}