#include<cstdio>
#include<iostream>
#include<cstring>
#define N 200005
using namespace std;

void getNext(int Next[],char b[],int len)
{
    memset(Next,0,sizeof(Next));
    Next[0]=-1;
    for(int i=0,j=-1;i<len;)
        if(j==-1||b[i]==b[j])
            Next[++i]=++j;
        else
            j=Next[j];
}
int kmp(char a[],char b[],int Next[])
{
    int n,len;
    n=strlen(a);
    len=strlen(b);
    getNext(Next,b,len);

    for(int i=0,j=0;i<n;)
    {
        if(j==-1||a[i]==b[j])i++,j++;
        else
            j=Next[j];
        if(j>=len)
            return 1;
    }
    return 0;
}

int Next[N];
char a[N],b[N];
char c[N*2];

int main()
{
    while(scanf("%s %s",a,b)==2)
    {
        strcpy(c,a);
        strcat(c,a);

        if(strlen(a)==strlen(b)&&kmp(c,b,Next))printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}