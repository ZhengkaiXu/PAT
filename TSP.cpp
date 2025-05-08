#include<cstdio>
#include<iostream>
#include<cstring>
#define N 1100000
using namespace std;

struct ss
{
    int v,next;
};
ss edg[2*N];
int head[N*2],sum_edge=0;

void addedge(int u,int v)
{
    edg[sum_edge]=(ss){v,head[u]};
    head[u]=sum_edge++;
}

int du[N];
int Stack[N],top=0;
int arr[N],c1=0;
int dp[N]={0};

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

int main()
{
    memset(head,-1,sizeof(head));
    int n,m,u,v;
    n=read();
    m=read();

    while(m--)
    {
        u=read();
        v=read();
        addedge(u,v);
        du[v]++;
    }

    for(int i=1;i<=n;i++)if(!du[i])Stack[top++]=i;

    while(top)
    {
        int now=Stack[--top];
        arr[c1++]=now;

        for(int i=head[now];i!=-1;i=edg[i].next)
        {
            v=edg[i].v;
            du[v]--;
            if(!du[v])Stack[top++]=v;
        }
    }

    int ans=0;

    for(int i=0;i<c1;i++)
    {
        u=arr[i];
        dp[u]++;
        ans=max(ans,dp[u]);
        for(int i=head[u];i!=-1;i=edg[i].next)
        {
            v=edg[i].v;
            dp[v]=max(dp[v],dp[u]);
        }
    }

    printf("%d\n",ans);
    return 0;
}