#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

int fac[]= {1, 1, 2, 6, 24, 120, 720, 5040, 40320}; //阶乘

int f(int x)
{
    int a[9],k=0;
    while(x)
    {
        a[k++]=x%10;
        x/=10;
    }
//    for(int i=0;i<k;i++)printf("%d",a[i]);
//    printf("\n");
    int ans=0,tmp;
    for(int i=0; i<k; i++)
    {
        tmp=0;//记录有几个比它小的数
        for(int j=i+1; j<k; j++)
        {
            if(a[j]<a[i])tmp++;
        }
        ans+=tmp*fac[k-i-1];
    }
    return ans;
}

int dis[45050]={0};
int q[45050],c1=0,c2=0;
int getnum(char a[])
{
    int ans=0;
    for(int i=0;i<8;i++)
    {
        ans*=10;
        ans+=a[i]-'0';
    }
    return ans;
}

void bfs()
{
    c1=0;
    c2=1;
    q[0]=12345678;
    dis[f(12345678)]=0;

    while(c1!=c2)
    {
        int now=q[c1++];


        int next;
        char a[10],b[10];
        sprintf(a,"%d",now);
        now=f(now);

        for(int i=7;i>=0;i--)b[i]=a[7-i];

        next=getnum(b);
        //printf("aaaa");
        int id=f(next);
        if(dis[id]==-1)
        {
            dis[id]=dis[now]+1;
            q[c2++]=next;
        }
        //58763214  a
        //87654321  b
        b[0]=a[1];
        b[1]=a[2];
        b[2]=a[3];
        b[3]=a[0];
        b[4]=a[7];
        b[5]=a[4];
        b[6]=a[5];
        b[7]=a[6];
        next=getnum(b);
        id=f(next);
        if(dis[id]==-1)
        {
            dis[id]=dis[now]+1;
            q[c2++]=next;
        }

        //51863724 a
        //58763214 b
        b[0]=a[0];
        b[1]=a[2];
        b[2]=a[5];
        b[3]=a[3];
        b[4]=a[4];
        b[5]=a[6];
        b[6]=a[1];
        b[7]=a[7];
        next=getnum(b);
        id=f(next);
        if(dis[id]==-1)
        {
            dis[id]=dis[now]+1;
            q[c2++]=next;
        }
    }
}


int main()
{
    memset(dis,-1,sizeof(dis));
    bfs();

    int n;
    scanf("%d",&n);
    while(n--)
    {
        int now=0;
        for(int i=0;i<8;i++)
        {
            int a;
            scanf("%d",&a);
            now*=10;
            now+=a;
        }

        printf("%d\n",dis[f(now)]);
    }
    return 0;
}