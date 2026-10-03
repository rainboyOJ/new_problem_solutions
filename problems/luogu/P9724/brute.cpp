/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 13:05
 * update_at: 2026-10-03 13:05
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：直接把题目里的过程建模成状态图。
//   状态 = (Pang 所在点 p, Shou 所在点 u)；
//   Shou 从 u 走到邻居 v 后结算伤害：
//     dist(p, v) <  d  ->  伤害 d - dist(p, v)，Pang 不动；
//     dist(p, v) >= d  ->  伤害 d，Pang 传送到 v。
//   边权非负，所以在 n*n 个状态上跑一次最短路即可。
// 复杂度 O(n*m + n^2 log n)，只适合 n 很小的数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXB = 65; // 暴力只支持 n <= 64
const long long INF = (1LL << 60);

int n, m, k, d;
vector<int> g[MAXB];

int dist_all[MAXB][MAXB];   // dist_all[s][v]：图上 s 到 v 的最短路
long long best[MAXB][MAXB]; // best[p][u]：Pang 在 p、Shou 在 u 时的最小累计伤害
bool done[MAXB][MAXB];

struct State {
    int p; // Pang 当前位置
    int u; // Shou 当前位置
    long long cost;

    bool operator < (const State &other) const {
        return cost > other.cost;
    }
};

// 无权图最短路，起点 s，距离写入 dist[]。
void bfs(int s, int dist[]) {
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> d;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int s = 1; s <= n; s++) {
        bfs(s, dist_all[s]);
    }

    for (int p = 1; p <= n; p++) {
        for (int u = 1; u <= n; u++) {
            best[p][u] = INF;
            done[p][u] = false;
        }
    }
    best[k][1] = 0;

    priority_queue<State> pq;
    State start;
    start.p = k;
    start.u = 1;
    start.cost = 0;
    pq.push(start);

    while (!pq.empty()) {
        int p = pq.top().p;
        int u = pq.top().u;
        long long cost = pq.top().cost;
        pq.pop();
        if (done[p][u]) {
            continue;
        }
        done[p][u] = true;

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            int dis = dist_all[p][v];
            long long nc;
            int np;
            if (dis < d) {
                nc = cost + (d - dis);
                np = p;
            }
            else {
                nc = cost + d;
                np = v;
            }
            if (nc < best[np][v]) {
                best[np][v] = nc;
                State next;
                next.p = np;
                next.u = v;
                next.cost = nc;
                pq.push(next);
            }
        }
    }

    // Shou 可能在 Pang 的任意位置上到达终点 n。
    long long ans = INF;
    for (int p = 1; p <= n; p++) {
        if (best[p][n] < ans) {
            ans = best[p][n];
        }
    }
    cout << ans << "\n";

    return 0;
}
