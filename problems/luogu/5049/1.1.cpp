/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-10 08:58:46
 */
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5e5 +5;
const int maxe = 3e6+5;
const int mod = 1e9+7;


int n,m;
int a[maxn];
int del_edge = 0; //枚举删除的边

typedef std::pair<int,int> edge;
std::vector<edge> adj[maxn];
std::vector<edge> edges;

// 边是否在环上
bool on_ring_edge[maxe*2];
bool on_ring_node[maxn];


void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        // debug
        #ifdef DEBUG
        
        std::cout << "id : " << i << " -> "  << u << " " << v ; std::cout  << "\n";
        #endif

        //next点 ,边的编号
        edges.push_back({u,v});
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::sort(adj[i].begin(),adj[i].end());
    }
}
std::vector<int> ans;
std::vector<int> tmp_ans;

// 回溯法找环: 原理: 找到环上的点,立刻回溯

struct p {int fa,eid;};
p parent[maxe*2];
bool vis[maxn];
bool find_loop = 0;
void dfs_find_loop(int u,int fa)  {
    if( find_loop ) return;
    // std::cout << "dfs " << u << "\n";
    vis[u] = 1;

    for(auto [v,eid] : adj[u]) {
        if( v == fa) continue;

        if( vis[v]) {
            find_loop = 1;

            int cur = u;

            on_ring_edge[eid] = 1;
            while(cur != v) {
                int eid = parent[cur].eid;
                on_ring_edge[eid] = 1;
                cur = parent[cur].fa;
            }

            return;
        }

        parent[v] = {u,eid};
        dfs_find_loop(v, u);
        if( find_loop) return;
    }
}


void dfs(int u,int fa) {
    
    tmp_ans.push_back(u);

    for( auto [v,id] : adj[u]) {
        if( id == del_edge) continue;
        if( v == fa) continue;
        dfs(v,u);
    }
}

// 找倒要删除的边
bool find_del_edge(int u,int fa,int target) {

#ifdef DEBUG
    std::cout << u << " target " << target << "\n";
#endif
    vis[u] = 1;
    for(int i = 0 ;i < adj[u].size() ;i++) {
        auto [v,eid] = adj[u][i];

        if( v == fa) continue;
        if( vis[v]) {
            // 这个时候,
            if( del_edge == 0) del_edge = eid;

            continue;
        }

        // 是不是最大的点
        // bool last_v = adj[u].back().first == v;
        // fix: 不要 last_v 只要是环上的边都要判断

        // 记录 下一个回溯会到达的点
        int next_point = target;

        // u 在环上
        if( on_ring_node[u]  && i + 1  < adj[u].size() && vis[adj[u][i+1].first] == 0) { 
            next_point = adj[u][i+1].first;
            // std::cout << u << " next_point " << next_point << "\n";
        }

        // 环上的点都要判断
        //找到删除的边
        if( on_ring_edge[eid] && v > next_point)
        {
            del_edge = eid;
            return 1;
        }

        if( find_del_edge(v, u,next_point)) return 1;

    }
    return 0;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    // 找环上的边
    // 1. topsort
    // 2. dfs法 -- >这里使用

    if( m == n-1) {
        dfs(1,0);
        for( auto u : tmp_ans) {
            std::cout << u << " ";
        }
        return 0;
    }


    dfs_find_loop(1, 0);
    // cout << " on_ring_edge: ";


    // 记录在环上的点
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        if( on_ring_edge[i])
        {
#ifdef DEBUG
            std::cout << i << " ";
#endif
            auto [u,v] = edges[i-1];
            on_ring_node[u]= 1;
            on_ring_node[v]= 1;
        }
    }

#ifdef DEBUG
    
    std::cout  << "\n";

    // debug: 输出环上的边
    // for( auto & i : loop ) {
    //     std::cout << "id : "  << i <<   endl;
    // }
#endif
    memset(vis,0,sizeof(vis));
    find_del_edge(1, 0,1e9);
#ifdef DEBUG
    std::cout << "del_edge = " << del_edge  << "\n";
    std::cout  << std::endl;
#endif

    dfs(1,0);
    for( auto u : tmp_ans) {
        std::cout << u << " ";
    }

    

    
    return 0;
}
