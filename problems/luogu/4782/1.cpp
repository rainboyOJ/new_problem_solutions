/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-20 14:36:25
 */
#include <bits/stdc++.h>
#include <stack>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];

std::vector<int> g[maxn]; // 存图

// 对以个点进行取反
int _not(int u) { 
    return u > n ? u-n : u+n;
}

void add_edge(int u,int v) {
    g[u].push_back(v);
}

// ======== tarjan scc
int dfn[maxn],low[maxn],timer;
int scc[maxn]; // 点的编号
bool in_stack[maxn];
int scc_cnt; //scc 编号,color
std::stack<int> stk;

void tarjan_scc(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    in_stack[u] = 1;

    for( auto v : g[u]) {
        if( !dfn[v])  
        {
            tarjan_scc(v);
            low[u] = min(low[u],low[v]);
        }
        else if( in_stack[v]) {  // 返祖边,且没有退出
            low[u] = min(low[u],dfn[v]);
        }

    }


    if( low[u] == dfn[u]) {
        scc_cnt++;
        while (1) {
            int t = stk.top(); stk.pop();
            in_stack[t] = 0; // 已经不再栈内
            scc[t] = scc_cnt; // 设置点的scc编号 
            if( t == u) break; // 退出
        }

    }

}


// ======== tarjan end

void init(){
    std::cin >> n >> m;
    int tm = m;
    while (tm--) {
        int i,a,j,b;
        std::cin >> i >> a >> j >> b;

        // 如果a == 1 此时的u就是i,否则就是i+n
        int u =  (a == 1) ? i : i+n;
        int notu = _not(u);

        int v =  (b == 1) ? j : j+n;
        int notv = _not(v);

        // 逻辑
        // 满足的条件 (u or v)
        // !u -> v and !v -> u
        add_edge(notu, v);
        add_edge(notv, u);

    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    for(int i = 1;i <= 2*n ;++i ) // i: 1->n
    {
        // 强连通
        if( !dfn[i] ) tarjan_scc(i);
        
    }

    //检查是否有解
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( scc[i] == scc[_not(i)] ) {
            std::cout << "IMPOSSIBLE" << "\n";
            return 0;
        }
    }

    std::cout << "POSSIBLE" << "\n";
    // 输出一个解
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        // 谁的scc编号小就选谁
        if( scc[i] < scc[_not(i)])
            std::cout << 1 << " ";
        else
            std::cout << 0 << " ";
    }

    
    return 0;
}
