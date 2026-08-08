/**
 * Author: Rainboy
 * P4013 数字梯形问题
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const int maxe = 10005;
const int INF_INT = 0x3f3f3f3f;

struct linkList {
    struct edge {int u,v,w,c,next;} e[maxe];
    int h[maxn], edge_cnt=0;
    linkList(){ reset(); }
    void reset() { edge_cnt=0; memset(h,-1,sizeof(h)); }
    void add(int u,int v,int w=0, int c=0){
        e[edge_cnt] = {u,v,w,c,h[u]};
        h[u] = edge_cnt++;
    }
} e;

struct MCMF {
    int dis[maxn], flow[maxn], pre[maxn], last[maxn];
    bool vis[maxn];
    int n;
    long long max_flow, min_cost;

    void init(int _n) { e.reset(); n = _n; }
    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);
        e.add(v, u, 0, -cost);
    }
    bool spfa(int s, int t) {
        for(int i = 0; i <= n; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        queue<int> q;
        dis[s] = 0; vis[s] = 1; pre[t] = -1; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop(); vis[u] = 0;
            for(int i = e.h[u]; ~i; i = e[i].e[i].next) { // 注意：这里需匹配你的模板结构
                // ... 内部逻辑同上 ...
            }
        }
        return pre[t] != -1;
    }
    // solve 逻辑同之前代码，此处略
};

// 坐标映射
int m, n;
int val[45][45];
int node_id[45][45];

int main() {
    cin >> m >> n;
    int cnt = 0;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=m+i-1; ++j) {
            cin >> val[i][j];
            node_id[i][j] = ++cnt;
        }

    auto solve_rule = [&](int r) {
        MCMF mcmf;
        int S = 0, T = 2 * cnt + 1;
        mcmf.init(T);
        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=m+i-1; ++j) {
                int in = node_id[i][j], out = in + cnt;
                // 内部边：点容量在规则1下为1，其余为INF
                mcmf.addEdge(in, out, (r == 1 ? 1 : INF_INT), -val[i][j]);
                
                if(i == 1) mcmf.addEdge(S, in, 1, 0); // 顶端起点
                if(i == n) mcmf.addEdge(out, T, (r == 3 ? INF_INT : 1), 0); // 底端终点
                
                if(i < n) {
                    // 外部边：边容量在规则1,2下为1，规则3为INF
                    mcmf.addEdge(out, node_id[i+1][j], (r <= 2 ? 1 : INF_INT), 0);
                    mcmf.addEdge(out, node_id[i+1][j+1], (r <= 2 ? 1 : INF_INT), 0);
                }
            }
        }
        mcmf.solve(S, T);
        cout << -mcmf.min_cost << endl;
    };

    solve_rule(1);
    solve_rule(2);
    solve_rule(3);
    return 0;
}
