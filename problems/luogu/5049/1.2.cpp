/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-10 21:18:55
 * desc: 对1.1.cpp 的复刻: 优化, 不用 on_ring_edge, 
 * 使用最简单的dfs 找环上所有点的代码
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5e5+5;

// --- 存图
std::vector<int> adj[maxn];
void add_edge(int u,int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}
// --- 存图 -- end

int n,m;
bool on_ring[maxn]; //点u是否在环上
int del_edge[2]; // (u,v) 是删除的边 u < v

inline bool is_del_edge(int u,int v) {
    if( u == del_edge[0] && v == del_edge[1] ) return 1;
    if( u == del_edge[1] && v == del_edge[0] ) return 1;
    return 0;
}

void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        add_edge(u, v);
    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::sort(adj[i].begin(),adj[i].end());
    }
}


int parent[maxn];
bool finded_loop = 0;
bool vis[maxn];
void dfs_find_loop(int u,int fa) {
    if( finded_loop) return;
    vis[u] = 1;

    for( auto v : adj[u]) {
        if( v == fa ) continue;

        if( vis[v]) {
            finded_loop = 1;

            int cur = u;
            on_ring[v] = 1;
            while( cur != v) {
                on_ring[cur] = 1;
                cur = parent[cur];
            }

            return;
        }
        
        parent[v] = u;
        dfs_find_loop(v, u);
        if( finded_loop) return;
    }

}

std::vector<int> ans;
void dfs(int u,int fa) {
    
    ans.push_back(u);

    for( auto v : adj[u]) {
        if( v == fa) continue;
        if( is_del_edge(u, v) ) continue;
        dfs(v,u);
    }
}


// target 记录到达点u的时候的 如果回溯可以到达的下一个点
bool find_del_edge(int u,int fa,int target){
    vis[u] = 1;

    for(int i = 0 ;i< adj[u].size() ;i++)
    {
        int v = adj[u][i];
        if( v == fa) continue;

        // 特殊情况 ,走到环上的最后了
        if( vis[v]) {
            del_edge[0] = u;
            del_edge[1] = v;
            continue;
        }

        // 这里 target 可能会变化
        int next_point = target;

        // 只有在环上的时候 才需要记录 ,下一个next_point
        // 应为断开环上的边后,一定会回溯到环上点的未访问的点
        if( on_ring[u]) {
            // 是否有比自己大的点
            if( i+ 1 < adj[u].size() && adj[u][i+1] != fa)
                next_point = adj[u][i+1];
        }

        // 尝试断开环上的边
        if(on_ring[u] &&  on_ring[v] && v > next_point) {
            del_edge[0] = u;
            del_edge[1] = v;
            return 1;
        }

        if( find_del_edge(v, u, next_point) )
            return 1;
        
    }

    return 0;

    
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    if( n -1 == m)
    {
        dfs(1,0);
        for( auto u : ans) std::cout << u << " ";
        return 0;
    }

    dfs_find_loop(1,0);
    #ifdef DEBUG
    std::cout << "on_ring node :" << "\n";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( on_ring[i] )
            std::cout << i << " ";
    }
    #endif

    memset(vis,0,sizeof(vis));
    find_del_edge(1,0,1e9);


    dfs(1,0);
    for( auto u : ans) std::cout << u << " ";
    
    return 0;
}
