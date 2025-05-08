#include<cstdio>
#include<cstring>
#define N 605000
using namespace std;
const unsigned long long base=27;

char s[N][45];

struct ss
{
    int index;
    unsigned long long h;

    bool operator < (const ss &s)const
    {
        if(h!=s.h)return h<s.h;
        return index<s.index;
    }
};
ss arr[N];
int vis[N]={0};
ss ls[N];

void sort(int l,int r)
{
    if(l==r)return;
    int mid=(l+r)/2;
    sort(l,mid);
    sort(mid+1,r);

    int c1=l,c2=mid+1;
    int c=l;

    while(c1<=mid&&c2<=r)
    {
        if(arr[c1]<arr[c2])ls[c++]=arr[c1++];
        else
            ls[c++]=arr[c2++];
    }

    while(c1<=mid)ls[c++]=arr[c1++];
    while(c2<=r)ls[c++]=arr[c2++];
    for(int i=l;i<=r;i++)arr[i]=ls[i];
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",s[i]);
        int len=strlen(s[i]);
        unsigned long long now=0;

        for(int j=0;j<len;j++)
        {
            now=now*base+s[i][j];
        }
        arr[i].index=i;
        arr[i].h=now;
    }

    sort(0,n-1);
    int c1=1;

    // for(int i=0;i<n;i++)printf("%llu %d\n",arr[i].h,arr[i].index);

    while(c1<n)
    {
        if(arr[c1].h==arr[c1-1].h)
        {
            vis[arr[c1].index]=1;
            while(arr[c1].h==arr[c1-1].h)c1++;
        }
        else
        {
            c1++;
        }
    }

    for(int i=0;i<n;i++)
        if(vis[i])printf("%s\n",s[i]);

    return 0;
}