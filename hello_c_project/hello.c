#include <stdio.h>

int main()
{
    int a = 5;
    int b = 10;
    int sum = a + b;

    printf("Hello, World!\n");
    printf("This is first C app written by Tadija\n");
    printf("The sum of %d and %d is %d\n", a, b, sum);
    printf("Press Enter to continue...\n");
    scanf("%*c", 1, NULL); // Wait for user input
    return 0;
}
