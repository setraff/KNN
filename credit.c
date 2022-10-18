#include <stdio.h>
#include <cs50.h>
#include <math.h>

int last(int n, unsigned long long int card_num);
unsigned long long int first(int n, unsigned long long int card_num);
int count_digit(unsigned long long int card_num);
bool check_amex(unsigned long long int card_num);
bool check_visa(unsigned long long int card_num);
bool check_mastercard(unsigned long long int card_num);
int main(void)
{
    // ask user for input
    unsigned long long int card_num;
    do
    {
        card_num = get_long("Enter card number: ");
    }
    while (card_num < 0);
    int sum = 0;
    // perform checksum
    // 1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ DIGITS together.
    for (int j = 2; j <= count_digit(card_num); j = j + 2)
    {
        int num = last(j, card_num);
        int doubled_num = num * 2;
        if (count_digit(doubled_num) > 1)
        {
            sum = sum + (last(1, doubled_num));
            sum = sum + (last(2, doubled_num));
        }
        else
        {
            sum = sum + doubled_num;
        }
    }
    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    for (int j = 1; j <= count_digit(card_num) + 1; j = j + 2)
    {
        int num = last(j, card_num);
        sum = sum + num;
    }
    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    if (last(1, sum) == 0)
    {
        if (check_amex(card_num) == true)
        {
            printf("AMEX\n");
        }
        else if (check_visa(card_num) == true)
        {
            printf("VISA\n");
        }
        else if (check_mastercard(card_num) == true)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// FUNCTIONS
// function to get any nth to last value from card_num
int last(int n, unsigned long long int card_num)
{
    unsigned long long int card_num_prototype = card_num % (unsigned long long int)pow(10, n);
    int last = card_num_prototype / (unsigned long long int)pow(10, n - 1);
    return last;
}
// function to get first n numbers in card_num
unsigned long long int first(int n, unsigned long long int card_num)
{
    return card_num / pow(10, count_digit(card_num) - n);
}
// function to calculate the number of digits in card_num
int count_digit(unsigned long long int card_num)
{
    return log10(card_num) + 1;
}
// check if AMEX: 15 digit numbers, starts with 34 or 37 (retuens a boolean expression)
bool check_amex(unsigned long long int card_num)
{
    if ((count_digit(card_num) == 15) && (first(2, card_num) == 34 || first(2, card_num) == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}
// checks if VISA: 13 and 16 digit numbers, starts with 4 (retuens a boolean expression)
bool check_visa(unsigned long long int card_num)
{
    if ((count_digit(card_num) == 13 || count_digit(card_num) == 16) && (first(1, card_num) == 4))
    {
        return true;
    }
    else
    {
        return false;
    }
}
// checks if MASTERCARD: 16 digit numbers, starts with 51, 52, 53, 54 or 55 (retuens a boolean expression)
bool check_mastercard(unsigned long long int card_num)
{
    if (((count_digit(card_num) == 16)) && (first(2, card_num) == 51 || first(2, card_num) == 52 || first(2, card_num) == 53
                                            || first(2, card_num) == 54 || first(2, card_num) == 55))
    {
        return true;
    }
    else
    {
        return false;
    }
}