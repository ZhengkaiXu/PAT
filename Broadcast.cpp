#include<cstdio>
#include<iostream>
#include<cstring>
#define N 30005
using namespace std;

struct ss
{
    int v,next;
};
ss edg[2*N];
int head[N],sum_edge=0;

void addedge(int u,int v)
{
    edg[sum_edge]=(ss){v,head[u]};
    head[u]=sum_edge++;
}

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

int color[N]={0};

int dfs(int x,int now_color)
{
    if(color[x]&&color[x]!=now_color)return 0;
    if(color[x]&&color[x]==now_color)return 1;
    color[x]=now_color;

    for(int i=head[x];i!=-1;i=edg[i].next)
    {
        int v=edg[i].v;
        if(!dfs(v,now_color*-1))return 0;
    }
    return 1;
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
        addedge(v,u);
    }

    for(int i=1;i<=n;i++)
        if(!color[i]&&!dfs(i,1))
        {
            printf("-1\n");
            return 0;
        }
    printf("1\n");
    return 0;
}