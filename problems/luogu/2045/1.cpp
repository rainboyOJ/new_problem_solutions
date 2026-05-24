/**
 * Author by Rainboy blog: https://blog.roj.ac.cn
 */

#include <bits/stdc++.h>
using namespace std;

// 使用你模板中的常量，确保空间充足
const int maxn = 1e5 + 5; 
const int maxe = 1e6 + 5; 
const int INF_INT = 0x3f3f3f3f;

struct linkList {
    typedef struct {int u,v,w,c,next;} edge; 
    edge e[maxe];
    int h[maxn], edge_cnt = 0;
    linkList() { reset(); }
    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }
    void add(int u, int v, int w = 0, int c = 0) {
        e[edge_cnt] = {u, v, w, c, h[u]};
        h[u] = edge_cnt++;
    }
    edge& operator[](int i) { return e[i]; }
} e;

struct MCMF {
    int dis[maxn], flow[maxn], pre[maxn], last[maxn];
    bool vis[maxn];
    int n;
    long long max_flow, min_cost;

    void init(int n) {
        e.reset();
        this->n = n;
    }

    void addEdge(int u, int v, int cap, int cost) {
        e.add(u, v, cap, cost);      
        e.add(v, u, 0, -cost);       
    }

    bool spfa(int s, int t) {
        for(int i = 0; i <= n + 1; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        queue<int> q;
        dis[s] = 0; vis[s] = 1; pre[t] = -1;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for(int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v;
                if (e[i].w > 0 && dis[v] > dis[u] + e[i].c) {
                    dis[v] = dis[u] + e[i].c;
                    pre[v] = u;
                    last[v] = i;
                    flow[v] = min(flow[u], e[i].w);
                    if (!vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t] != -1;
    }

    void solve(int s, int t) {
        max_flow = 0; min_cost = 0;
        while (spfa(s, t)) {
            int f = flow[t];
            max_flow += f;
            min_cost += (long long)f * dis[t];
            int now = t;
            // 修正：严格按照路径回溯更新残余网络
            while (now != s) {
                int edge_idx = last[now];
                e[edge_idx].w -= f;
                e[edge_idx ^ 1].w += f;
                now = pre[now];
            }
        }
    }
} mcmf;

// 坐标转换逻辑：入点为 id，出点为 id + n*n
int get_id(int r, int c, int n, bool out) {
    int id = (r - 1) * n + c;
    return out ? id + n * n : id;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k;
    if (!(cin >> n >> k)) return 0;

    int S = 0, T = 2 * n * n + 1;
    mcmf.init(T);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val; cin >> val;
            int in_node = get_id(i, j, n, false);
            int out_node = get_id(i, j, n, true);

            // 1. 格子内部拆点连边：第一趟有收益，后续无收益
            mcmf.addEdge(in_node, out_node, 1, -val);
            mcmf.addEdge(in_node, out_node, k, 0); // 容量给 k 确保后续路径可通行

            // 2. 只有 Out 点才能向下一个 In 点移动
            if (j + 1 <= n) 
                mcmf.addEdge(out_node, get_id(i, j + 1, n, false), k, 0);
            if (i + 1 <= n) 
                mcmf.addEdge(out_node, get_id(i + 1, j, n, false), k, 0);
        }
    }

    // 源点进 (1,1)，(n,n) 出到汇点
    mcmf.addEdge(S, get_id(1, 1, n, false), k, 0);
    mcmf.addEdge(get_id(n, n, n, true), T, k, 0);

    mcmf.solve(S, T);
    cout << -mcmf.min_cost << endl;

    return 0;
}
