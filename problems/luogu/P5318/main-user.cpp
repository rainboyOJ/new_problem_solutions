/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 01月 16日 星期日 14:48:43 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){	//构造函数
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }
    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }
    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    edge& operator[](int i){
        return e[i];
    }
} e;

vector<pair<int,int>> v1;

bool vis[maxn];
void dfs(int u){
    vis[u] = 1;
    printf("%d ",u);
    int i;
    e.for_each(u, [&](int u,int v,int w){
        if(vis[v] == 0){
            vis[v] = 1;
            dfs(v);
        }
    });
}

void bfs(int u){
    queue<int> q;
    vis[u] = 1;
    q.push(u);
    while ( !q.empty() ) {
        int u = q.front();
        q.pop();
        printf("%d ",u);
        int i;
        e.for_each(u, [&](int u,int v,int w){
            if(vis[v] == 0){
                vis[v] = 1;
                q.push(v);
            }
        });
    }
}

int main(int argc,char * argv[]){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        //v1.emplace_back(u,v);
        v1.push_back(std::make_pair(u,v));
    }
    sort(v1.begin(),v1.end());
    //std::reverse(v1.begin(), v1.end());
    //for (const auto& ee : v1) {
        //e.add(ee.first,ee.second);
    //}
    for(int i = v1.size()-1; i>=0;i--){
        e.add(v1[i].first, v1[i].second);
    }
    dfs(1);
    printf("\n");
    memset(vis,0,sizeof(vis));
    bfs(1);
    return 0;

}

