#include <stdio.h>
int main()
{
    int rows, coef = 1, s, i, j;

    printf("Enter number of rows: ");
    scanf("%d",&rows);

    for(i=0; i<rows; i++)
    {
        for(int =1; s <= rows-i; s++)
            printf("  ");

        for(j=0; j <= i; j++)
        {
            if (j==0 || i==0)
                coef = 1;
            else
                coef = coef*(i-j+1)/j;

            printf("%4d", coef);
        }
        printf("\n");
    }

    return 0;
}
