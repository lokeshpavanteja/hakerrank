#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int distinct_count(const char *s) {
    int seen[26] = {0};
    int count = 0;
    while (*s) {
        int idx = *s - 'a';
        if (!seen[idx]) {
            seen[idx] = 1;
            ++count;
        }
        ++s;
    }
    return count;
}

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    
    return -strcmp(a, b);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int da = distinct_count(a);
    int db = distinct_count(b);
    if (da != db) return da - db;
    return strcmp(a, b);
}

int sort_by_length(const char* a, const char* b) {
    int la = strlen(a);
    int lb = strlen(b);
    if (la != lb) return la - lb;
    return strcmp(a, b);
}

void string_sort(char** arr, const int len, int (*cmp_func)(const char* a, const char* b)) {
   
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (cmp_func(arr[i], arr[j]) > 0) {
                char *tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}



int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}