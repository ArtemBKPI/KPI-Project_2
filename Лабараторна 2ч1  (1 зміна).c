#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double x, y;
    
    printf("Enter x:");
    scanf("%lf", &x);
    
    if(x >= -5 && x < 0)
        y = pow(x, 2) + 2*x + 1;
    else if (x >= 0 && x < 10)
        y = sqrt(x + 1) - 1.0 / sqrt(x + 5);
    else if (x >= 10 && x < 1000)
        y = log10(x) + 2*x;
    else
        y = x / 2.0;
        
    system("cls");
    printf("x = %lf", x);
    printf("\ny = %lf", y);
    return 0;
}