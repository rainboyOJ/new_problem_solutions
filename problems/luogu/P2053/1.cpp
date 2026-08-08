/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * 题目：P2053 [SCOI2007] 修车
 * 思路：费用流。将每个技术人员拆分为 N 个节点，表示该技术人员倒数第 p 次修理。
 * 若某辆车是该工人的倒数第 p 个修理的，那么它及其后面修理的共 p 个人都要等待这段时间。
 * 故产生的贡献（费用）为 p * T_{i,j}。
 */

#include <bits/stdc++.h>
using namespace std;

// 节点数最大值：源点+汇点+车(60)+工人拆点(9*60) = 602
const int maxn = 1000; 
// 边数最大值：S->车(60) + 拆点->T(540) + 车->拆点(60*540) = 33000。注意反向边翻倍
const int maxe = 100000; 
const int INF_INT = 0x3f3f3f3f;

struct linkList {
    struct edge {int u,v,w,c,next;};
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
        for(int i = 0; i <= n; i++) dis[i] = INF_INT, vis[i] = 0, flow[i] = INF_INT;
        queue<int> q;
        dis[s] = 0; vis[s] = 1; pre[t] = -1;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for(int i = e.h[u]; ~i; i = e[i].next) {
                int v = e[i].v, cap = e[i].w, cost = e[i].c;
                if (cap > 0 && dis[v] > dis[u] + cost) {
                    dis[v] = dis[u] + cost;
                    pre[v] = u;
                    last[v] = i;
                    flow[v] = min(flow[u], cap);
                    if (!vis[v]) { vis[v] = 1; q.push(v); }
                }
            }
        }
        return pre[t] != -1;
    }

    void solve(int s, int t) {
        max_flow = 0; min_cost = 0;
        while (spfa(s, t)) {
            int now = t, f = flow[t];
            max_flow += f;
            min_cost += (long long)f * dis[t];
            while (now != s) {
                int idx = last[now];
                e[idx].w -= f;
                e[idx ^ 1].w += f;
                now = pre[now];
            }
        }
    }
} mcmf;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int M, N; // M 技术人员, N 顾客
    if (!(cin >> M >> N)) return 0;

    int S = 0, T = N + M * N + 1;
    mcmf.init(T);

    // 1. 源点向每辆车连边，流量1，费用0
    for (int i = 1; i <= N; ++i) {
        mcmf.addEdge(S, i, 1, 0);
    }

    // 2. 读取修理时间，并向技术人员的每个“倒数位置”连边
    for (int i = 1; i <= N; ++i) { // 第 i 辆车
        for (int j = 1; j <= M; ++j) { // 第 j 位技术人员
            int time; cin >> time;
            for (int p = 1; p <= N; ++p) { // 该工人的倒数第 p 个修理位
                // 费用计算：倒数第 p 个修，会贡献 p 次该车的修理时间
                int tech_pos_node = N + (j - 1) * N + p;
                mcmf.addEdge(i, tech_pos_node, 1, p * time);
            }
        }
    }

    // 3. 每个技术人员的每个修理位向汇点连边，流量1，费用0
    for (int j = 1; j <= M; ++j) {
        for (int p = 1; p <= N; ++p) {
            int tech_pos_node = N + (j - 1) * N + p;
            mcmf.addEdge(tech_pos_node, T, 1, 0);
        }
    }

    mcmf.solve(S, T);

    // 平均等待时间 = 总等待时间 / N
    cout << fixed << setprecision(2) << (double)mcmf.min_cost / N << endl;

    return 0;
}
