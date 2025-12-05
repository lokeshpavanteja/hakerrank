#include <stdio.h>

void calculate_the_maximum(int n, int k) 
{
    int max_and = 0;
    int max_or = 0;
    int max_xor = 0;

    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            
            int and_v = a & b;
            if (and_v < k && and_v > max_and)
                max_and = and_v;

            int or_v = a | b;
            if (or_v < k && or_v > max_or)
                max_or = or_v;

            int xor_v = a ^ b;
            if (xor_v < k && xor_v > max_xor)
                max_xor = xor_v;
        }
    }

    printf("%d\n%d\n%d\n", max_and, max_or, max_xor);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    calculate_the_maximum(n, k);

    return 0;
}
