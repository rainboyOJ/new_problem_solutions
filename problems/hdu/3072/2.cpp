#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const int maxn=50005;
int n,m;
struct Edge{ int v,d;
    Edge(int v=0,int d=0):v(v),d(d){}
};
vector<Edge>G[maxn];
stack<int>sta;
int dfn,scc_cnt,id[maxn],low[maxn],sccid[maxn];
int mind[maxn];

void tarjan(int u){
    id[u]=low[u]=++dfn;
    sta.push(u);
    for(Edge e:G[u]){ int v=e.v;
        if(!id[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(!sccid[v])
            low[u]=min(low[u],id[v]);
    }
    if(low[u]==id[u]){
        mind[++scc_cnt]=inf;
        for(;;){
            int x=sta.top();sta.pop();
            sccid[x]=scc_cnt;
            if(x==u)break;
        }
    }
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<n;i++){
            G[i].clear();id[i]=sccid[i]=0;
        }
        for(int i=1,a,b,c;i<=m;i++){
            scanf("%d%d%d",&a,&b,&c);
            G[a].push_back(Edge(b,c));
        }
        dfn=scc_cnt=0;
        for(int i=0;i<n;i++)
            if(!id[i])tarjan(i);
        for(int u=0;u<n;u++)
            for(Edge&e:G[u]){
                int v=e.v,d=e.d;
                if(sccid[u]!=sccid[v])
                    mind[sccid[v]]=min(mind[sccid[v]],d);
            }
        ll sum=0;
        for(int i=1;i<=scc_cnt;i++)
            if(mind[i]!=inf)sum+=mind[i];
        printf("%lld\n",sum);
    }
    return 0;
}
