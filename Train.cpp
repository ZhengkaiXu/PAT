#include<cstdio>
#include<iostream>
#define N 1700000
using namespace std;
int array1[N];
int ans2[N];
int StackArr1[N],toNum=0;
int read()
{
    int now=0;
    char ch=getchar();
    while(!(ch>='0'&&ch<='9'))ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        now=now*10+ch-'0';
        ch=getchar();
    }
    return now;
}
int main() {
    int n,m;
    n=read();
    m=read();
    //scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)array1[i]=read();
    //scanf("%d",&array1[i]);
    int now=1;
    int c1=0;
    for(int i=1;i<=n;i++)
    {
        ans2[c1++]=1;
        StackArr1[toNum++]=i;

        if(toNum>m)break;

        while(toNum>0&&StackArr1[toNum-1]==array1[now])
        {
            ans2[c1++]=2;
            now++;
            toNum--;
        }
    }
    if(toNum) {
        printf("No\n");
        return 0;
    }
    for(int i=0;i<c1;i++)
        if(ans2[i]==1)printf("push\n");
        else
            printf("pop\n");
    return 0;
}