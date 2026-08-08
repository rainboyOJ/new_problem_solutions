/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-19 10:21:45
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e6+5;
int n,m;
int a[maxn];

vector<int> adj[maxn];
int cur[maxn]; // 当前弧优化：记录adj[u]遍历到了第几条边
vector<int> path; // 存储结果路径

void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int u) {
    for(int &i = cur[u] ;i < adj[u].size() ; ) {
        int v = adj[u][i];
        i++; // 这一步相当于“删边”，指针后移
        dfs(v);
    }
    path.push_back(u);
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    init();
    dfs(1);

    for( auto u :path){
        std::cout << u << "\n";
    }
    
    return 0;
}
