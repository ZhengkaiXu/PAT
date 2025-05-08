#include<cstdio>
#include<iostream>
#include<cstring>
#define N 4000500
using namespace std;

struct ss
{
    int lson,rson;
};
ss tree[N];
int a[N],b[N];
long long pa[N]={0},pb[N]={0};


void dfs(int l1,int r1,int l2,int r2)
{
    if(l1>r1)return;
    if(l1==r1)return;

    int root=a[l1];
    l1++;
    r2--;

    int mid1,mid2;
    for(mid1=l1,mid2=l2;;mid1++,mid2++)
    {
        if(a[l1]==b[mid2])break;
    }

    tree[root].lson=a[l1];
    tree[root].rson=a[mid1+1];

    dfs(l1,mid1,l2,mid2);
    dfs(mid1+1,r1,mid2+1,r2);
    return ;
}

void print(int x)
{
    if(tree[x].lson)print(tree[x].lson);
    printf("%d ",x);
    if(tree[x].rson)print(tree[x].rson);
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),pa[i]=pa[i-1]+a[i];
    for(int i=1;i<=n;i++)scanf("%d",&b[i]),pb[i]=pb[i-1]+b[i];
    for(int i=1;i<=n;i++)tree[i].lson=tree[i].rson=0;

    dfs(1,n,1,n);

    int root=a[1];
    print(root);
    return 0;
}