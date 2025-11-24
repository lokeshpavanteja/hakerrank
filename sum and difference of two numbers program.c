#include <stdio.h>

int main()
{
   int x,y;
   float a,b;
   scanf("%d%d",&x,&y);
   scanf("%f%f",&a,&b);
   int sum=x+y;
   int diff=x-y;
   printf("%d %d\n",sum,diff);
   float s=a+b;
   float d=a-b;
   printf("%.1f %.1f",s,d);
    
    
    return 0;
}
