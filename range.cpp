#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1e7+10;
int a[N];
int main()
{
    int n,m,current;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&current);
        a[current]=1;
    }
    for(int i=1;i<N;i++)
    {
        a[i]=a[i-1]+a[i];
    }
    for(int i=0;i<m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",a[y]-a[x-1]);
    }
    return 0;
}