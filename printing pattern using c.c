#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n;
    scanf("%d", &n);

    int size = 2 * n - 1;
    int center = n - 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val = abs(i - center);
            int val2 = abs(j - center);
            int num = (val > val2 ? val : val2) + 1;
            printf("%d ", num);
        }
        printf("\n");
    }

    return 0;
}
