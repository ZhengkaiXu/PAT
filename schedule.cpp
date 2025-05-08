#include <cstdio>
#include<iostream>
#include<cstring>
#define N 4000050
using namespace std;

struct ss
{
    long long x;
    char y[10];

    bool operator < (const ss &s)const
    {
        if(x!=s.x)return x>s.x;

        if(strcmp(y,s.y)>0)return 1;
        else
            return 0;
    }
};

class heap
{
private:
    ss arr[N];
    int sum_element;

    void filterup(int pos)
    {
        int fa=pos/2;
        ss value=arr[pos];

        while(pos>1)
        {
            if(!(arr[fa]<value))break;
            arr[pos]=arr[fa];
            pos=fa;
            fa=pos/2;
        }
        arr[pos]=value;
    }

    void filterdown(int pos)
    {
        int ch=pos*2;
        ss value=arr[pos];

        while(ch<=sum_element)
        {
            if(ch<sum_element&&arr[ch]<arr[ch+1])ch++;

            if(!(value<arr[ch]))break;
            arr[pos]=arr[ch];
            pos=ch;
            ch=pos*2;
        }
        arr[pos]=value;
    }

public:

    heap()
    {
        sum_element=0;
    }

    void insert(ss value)
    {
        arr[++sum_element]=value;
        filterup(sum_element);
    }

    void pop()
    {
        if(!sum_element)return;
        arr[1]=arr[sum_element--];
        filterdown(1);
    }

    ss top()
    {
        return arr[1];
    }

    bool empty()
    {
        if(sum_element)return 0;
        return 1;
    }
    void print()
    {
        for(int i=1;i<=sum_element;i++)printf("%lld %s\n",arr[i].x,arr[i].y);
    }
};

heap q;

int main()
{
    /* int n,nn;
     scanf("%d",&n);
     nn=n;
     while(n--)
     {
         ss now;
         scanf("%lld %s",&now.x,now.y);
         q.insert(now);
     }

     q.print();
     while(nn--)
     {
         printf("%lld %s\n",q.top().x,q.top().y);
         printf("\n");
         q.pop();
     }
 */
    int n,m;
    ss now;
    scanf("%d %d",&n,&m);
    while(n--)
    {
        scanf("%lld %s",&now.x,now.y);
        q.insert(now);
    }

    while(!q.empty()&&m--)
    {
        now=q.top();
        q.pop();
        printf("%s\n",now.y);
        now.x*=2;

        if(now.x<(1ll<<32))q.insert(now);
    }
    return 0;
}