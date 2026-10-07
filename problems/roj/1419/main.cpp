/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:12
 * update_at: 2026-10-07 15:12
 */
// main.cpp：SPFA（队列优化的 Bellman-Ford）求 1 到 n 的最短路，允许负权边。
// 数据范围：N<=20000, M<=40000, -1e9<=D<=1e9，保证无负环且 1 可达 n。
// 答案最负约 -(n-1)*1e9 ≈ -2e13，必须用 long long，INF 也要远大于这个量级。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20005; // 最大点数，多开几个防止越界
const int MAXM = 40005; // 最大边数
const ll INF = 4e18;    // 松弛起点：比最负路径 -2e13 大若干个数量级

// 链式前向星存图：适合边数上万、又要按点遍历出边的场景
int head[MAXN]; // head[u]：点 u 的第一条出边编号，0 表示没有出边
int nxt[MAXM];  // 同一起点的下一条出边编号
int to[MAXM];   // 边的终点
ll wt[MAXM];    // 边的权值
int edge_cnt;   // 已经加入的边数

ll dist[MAXN];  // dist[u]：从 1 到 u 的当前最短距离
bool inq[MAXN]; // inq[u]：点 u 是否正在队列里，防止同一时刻重复入队

int n, m;

// 加入一条 u -> v 的权值为 w 的有向边
void add_edge(int u, int v, ll w) {
    edge_cnt++;
    to[edge_cnt] = v;
    wt[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// SPFA 求以 1 为源点的最短路；无负环时队列必然收敛
void spfa() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        inq[i] = false;
    }
    deque<int> q; // 用双端队列，配合下面的 SLF 小优化
    dist[1] = 0;
    q.push_back(1);
    inq[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        inq[u] = false;
        // 只有 dist[u] 刚刚变小的点才可能松弛邻居，这正是 SPFA 比 Bellman-Ford 快的原因
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            ll nd = dist[u] + wt[e];
            if (nd < dist[v]) { // 找到更短的路，v 需要重新入队
                dist[v] = nd;
                if (!inq[v]) {
                    inq[v] = true;
                    // SLF：估计距离比队首还小的点优先处理，实测能减少入队次数
                    if (!q.empty() && dist[v] < dist[q.front()]) {
                        q.push_front(v);
                    } else {
                        q.push_back(v);
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int s, t;
        ll d;
        cin >> s >> t >> d;
        add_edge(s, t, d); // 重边与自环直接照常加入即可
    }

    spfa();

    cout << dist[n] << "\n"; // 题目保证 1 可达 n，dist[n] 不会是 INF
    return 0;
}
