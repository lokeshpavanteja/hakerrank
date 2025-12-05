#include <stdio.h>

void update(int *a, int *b) 
{
    int sum = *a + *b;
    int diff = *a - *b;

    if (diff < 0)
        diff = -diff;

    *a = sum;
    *b = diff;
}

int main() {
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);

    update(&a, &b);

    printf("%d\n%d", a, b);

    return 0;
}
