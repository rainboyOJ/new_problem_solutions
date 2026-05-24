/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-10 08:58:46
 */
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5005;
const int maxe = 4e6+5;
const int mod = 1e9+7;


int n,m;
int a[maxn];
int del_edge = 0; //枚举删除的边

typedef std::pair<int,int> edge;
std::vector<edge> adj[maxn];



void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        // debug
        // std::cout << "id : " << i << " -> "  << u << " " << v ; std::cout  << "\n";

        //next点 ,边的编号
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

std::vector<int> loop; //记录环上的边
// 回溯法找环: 原理: 找到环上的点,立刻回溯
bool vis[maxn];
int dfs_find_loop(int u,int fa)  {

    // 表示找到了, 返回环上的其实点
    if( vis[u] ) return u; 

    vis[u] = 1;

    for(auto [v,id] : adj[u]) {
        if( v == fa) continue;

        int loop_first = dfs_find_loop(v, u);

        if( loop_first ) {
            loop.push_back(id);
            vis[u] = 2; //标记是环上的点
            return u == loop_first ? 0 : loop_first;
        }
    }

    return 0; //表示没有找到
}


void dfs(int u,int fa) {
    
    tmp_ans.push_back(u);

    for( auto [v,id] : adj[u]) {
        if( id == del_edge) continue;
        if( v == fa) continue;
        dfs(v,u);
    }
}

// ans 里面存的序列 比 tmp_ans 大
// 字典序比较
bool compare_ans() {
    if( ans.size() == 0 ) return 1;
    
    for(int i = 0 ; i < ans.size();i++) {
        if( ans[i] > tmp_ans[i])
            return 1;
        else if( ans[i] < tmp_ans[i])
            return 0;
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
    // debug: 输出环上的边
    // for( auto & i : loop ) {
    //     std::cout << "id : "  << i <<   endl;
    // }

    
    for( auto  i : loop ) {
        tmp_ans.clear();
        del_edge = i;
        dfs(1,0);


        //debug
        // std::cout <<" del -> " << i  << "\n";
        // for( auto u : tmp_ans) std::cout << u << " ";
        // std::cout << "\n";

        if( compare_ans()) std::swap(tmp_ans,ans);

        // for( auto u : ans) std::cout << u << " ";
        // std::cout  << "\n";
        // std::cout  << "\n";
        // std::cout  << "\n";
    }

    for( auto u : ans) std::cout << u << " ";

    
    return 0;
}
