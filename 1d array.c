#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;  
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    printf("%lld", sum);

    free(arr); 
    return 0;
}
