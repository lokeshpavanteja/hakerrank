#include <stdio.h>

int main() 
{
    char ch;
    char str[50];
    char sen[100];
    scanf("%c",&ch);
    scanf("%s",&str);
    getchar();
    fgets(sen,100,stdin);
    printf("%c\n",ch);
    printf("%s\n",str);
    printf("%s",sen);
        
    return 0;
}
