#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
const int maxm=3005;
const int INF=1e9;

int t,n,m;
int d[maxn];
struct Edge{
    int v,w;
    Edge *next;
}pool[2*maxm],*h[maxn];
int cnt=0;
void Add_Edge(int u,int v,int w)
{
    Edge *p=&pool[cnt++];
    p->v=v;p->w=w;p->next=h[u],h[u]=p;
    if(w>=0)
    {
        Edge *q=&pool[cnt++];
        q->v=u;q->w=w;q->next=h[v],h[v]=q;  
    }
}

bool Bellman_Ford()
{
    fill(d,d+n+1,INF);
    d[1]=0;
    bool flag=false;
    for(int k=0;k<n;k++)
    {
        flag=false;
        for(int i=1;i<=n;i++)
        {
            if(d[i]<INF)
            {
                for(Edge *p=h[i];p;p=p->next)
                {
                    if(d[p->v]>d[i]+p->w)
                    {
                        d[p->v]=d[i]+p->w;
                        flag=true;
                    }
                }
            }
        }
        if(!flag) break;
    }
    return flag;
}
int main() 
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        cnt=0;
        for(int i=0;i<=n;i++) h[i]=NULL;//重置h[i] 
        int u,v,w;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            Add_Edge(u,v,w);
        }
        if(Bellman_Ford()) printf("YE5\n");
        else printf("N0\n");
    }
    return 0;
}
