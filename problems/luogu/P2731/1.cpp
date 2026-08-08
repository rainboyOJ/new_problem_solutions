/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-19 09:45:16
 */
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int g[505][505];
int deg[505];
std::vector<int> path;

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int u,v;
        std::cin >> u >> v;
        g[u][v]++;
        g[v][u]++;
        deg[u]++;
        deg[v]++;
    }
}

void dfs(int u) {
    // std::cout << u << "\n";
    for(int v = 1;v <= 500 ;++v ) // i: 1->500
    {
        if( g[u][v] > 0) {

            //删除边
            g[u][v] --;
            g[v][u] --;
            dfs(v);
        }
    }
    //回溯的时候加入点
    path.push_back(u);
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    int start_node = -1;
    for(int i = 1;i <= 500 ;++i ) // i: 1->505
    {
        if( deg[i] == 0) continue;

        //记录第一个可行的点
        if(start_node == -1 ) start_node = i;


        if( deg[i] % 2 == 1) 
        {
            start_node = i;
            break;
        }
    }
    dfs(start_node);
    for(int i = path.size()-1;i >=0 ;i--)
    {
        cout << path[i] <<"\n";
    }
    
    return 0;
}
