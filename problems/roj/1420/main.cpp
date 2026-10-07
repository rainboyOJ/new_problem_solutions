/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:11
 * update_at: 2026-10-07 15:11
 */
// main.cpp：一本通 1420《Dijkastra(II)》，无向连通图求点 1 到点 n 的最短路。
// 与 main.py 同一算法：链式前向星存图 + 小根堆优化的 Dijkstra。
// 边权 0 ≤ d ≤ 1e9，最长路径可达约 2e5 * 1e9 = 2e14，距离必须用 long long。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;                  // N ≤ 200000
const int MAXM = 400005;                  // M ≤ 400000
const ll INF = 4000000000000000000LL;     // 比任何可能的最短路（约 2e14）都大得多

int n, m;                                 // 点数、边数
int head[MAXN];                           // head[u]：点 u 的第一条出边编号，0 表示没有出边
int to[2 * MAXM];                         // to[e]：第 e 条边的终点
int nxt[2 * MAXM];                        // nxt[e]：同一个起点的下一条边编号
int wt[2 * MAXM];                         // wt[e]：边权，0 ≤ d ≤ 1e9，用 int 存足够
int edge_cnt;                             // 已经加入的边数（无向边要加两条）

ll dis[MAXN];                             // dis[u]：当前已知的 1 到 u 的最短距离
bool done[MAXN];                          // done[u]：u 是否已经出堆定稿

// 加一条有向边 u -> v，权值为 d。
void add_edge(int u, int v, int d) {
    edge_cnt++;
    to[edge_cnt] = v;
    wt[edge_cnt] = d;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        if (s == t) continue;   // 自环对最短路没有任何贡献（样例里就有 2 2 0）
        add_edge(s, t, d);      // 无向边：正反各加一条
        add_edge(t, s, d);
    }
}

// 堆优化 Dijkstra：每个点只在第一次出堆时定稿，输出 dis[n]。
void solve() {
    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[1] = 0;

    // 小根堆，元素是 pair<距离, 点号>，距离小的先出堆
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;
    heap.push(make_pair(0LL, 1));

    while (!heap.empty()) {
        pair<ll, int> top = heap.top();
        heap.pop();
        int u = top.second;
        if (done[u]) continue;  // 同一个点的旧距离可能被压入多次，只认第一次
        done[u] = true;
        if (u == n) break;      // 点 n 已经定稿，后面的堆项不可能让答案更小

        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (!done[v] && dis[u] + wt[e] < dis[v]) {   // 松弛成功才入堆
                dis[v] = dis[u] + wt[e];
                heap.push(make_pair(dis[v], v));
            }
        }
    }

    cout << dis[n] << "\n";     // 图保证连通，dis[n] 一定可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
