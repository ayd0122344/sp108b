#include<stdio.h>
int main(){
    int a[5]={0},*p=&a[0];
    printf("%d\n",p);
    printf("%d\n",*p);

    printf("please input 5 number!\n");
    for(int i=0;i<=4;i++){
    scanf("%d\n",p+i);
    }
    for(int j=0;j<=4;j++){
        *(p+j)=*(p+j)*2;
        printf("%d\n",*(p+j));
    }
    printf("\n");
    return 0;
}