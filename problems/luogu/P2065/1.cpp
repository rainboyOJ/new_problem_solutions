/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12 20:04:52
 * Problem: P2065 [TJOI2011] 卡片 (GCD 朴素连边版)
 * Algorithm: Max Flow (Dinic) + Brute Force GCD
 */

#include <bits/stdc++.h>
using namespace std;

// 点数：500 (蓝) + 500 (红) + 源汇 ≈ 1005
const int maxn = 1005; 
// 边数：最坏情况每对都连边 500*500 = 250,000。
// 网络流存双向边，所以数组要开到 500,000 以上
const int maxe = 600005; 
const long long INF = 1e18;

// --- 存图模板 ---
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }
} e;

// --- Dinic算法模板 ---
struct Dinic {
    vector<int> level, cur;
    int n;
    
    void init(int n) {
        e.reset(); // 清空边
        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边
        e.add(v, u, 0);      // 反向边
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v, cap = e[i].w;
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] >= 0;
    }
    
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            int v = e[cid].v;
            int cap = e[cid].w;
            
            if (level[u] + 1 != level[v] || cap <= 0) continue;
            
            long long tr = dfs(v, t, min(preFlow, (long long)cap));
            
            if (tr == 0) continue;

            e[cid].w -= tr;
            e[cid ^ 1].w += tr;
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        return flow;
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            for (int i = 0; i <= n; i++) cur[i] = e.h[i];
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// 全局变量
int m, n;
vector<int> blue_vals;
vector<int> red_vals;

void solve() {
    cin >> m >> n;
    
    blue_vals.resize(m);
    for(int i = 0; i < m; ++i) cin >> blue_vals[i];
    
    red_vals.resize(n);
    for(int i = 0; i < n; ++i) cin >> red_vals[i];

    // 节点分配规划:
    // S = 0
    // Blue Cards: 1 ~ m
    // Red Cards: m+1 ~ m+n
    // T = m + n + 1
    
    int s = 0;
    int t = m + n + 1;
    
    // 初始化 Dinic
    dinic.init(t + 1); 

    // 1. 构建源点 -> 蓝色卡片
    for (int i = 0; i < m; i++) {
        // 蓝色卡片编号: i + 1
        dinic.addEdge(s, i + 1, 1);
    }

    // 2. 构建红色卡片 -> 汇点
    for (int i = 0; i < n; i++) {
        // 红色卡片编号: m + 1 + i
        dinic.addEdge(m + 1 + i, t, 1);
    }

    // 3. 构建蓝色卡片 -> 红色卡片 (暴力枚举)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 如果两个数有公约数 (gcd > 1)，则可以匹配
            // __gcd 是 GCC 内置函数，也可以用 std::gcd (需 <numeric>)
            if (std::gcd(blue_vals[i], red_vals[j]) > 1) {
                // 连边: Blue(i+1) -> Red(m+1+j)
                dinic.addEdge(i + 1, m + 1 + j, 1);
            }
        }
    }
    
    cout << dinic.maxFlow(s, t) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
