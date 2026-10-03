/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 13:05
 * update_at: 2026-10-03 13:05
 */
// main.cpp：[EC Final 2022] Chase Game 的正解。
// 思路：把追逃过程分成“传送之前 / 第一次传送之后”两段。
//   - 传送之前 Pang 一直待在 k，Shou 走到每个点的最小伤害是一次带权最短路。
//   - 一旦 Pang 在某点 v 传送，之后两人的相对位置重新由 v 决定，
//     剩余伤害只和 dist(v, n) 有关，可以用等差数列公式直接算出。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = (1LL << 62);

int n, m, k, d;
vector<int> g[MAXN]; // 邻接表

long long dist_k[MAXN];    // dist_k[v]：k 到 v 的图上最短路（Pang 不动的依据）
long long dist_n[MAXN];    // dist_n[v]：n 到 v 的图上最短路（传送后还要走多远）
long long dist_shou[MAXN]; // dist_shou[u]：Pang 仍停在 k 时，Shou 走到 u 的最小累计伤害
bool vis[MAXN];

struct PQNode {
    int u;
    long long dist;

    bool operator < (const PQNode &other) const {
        return dist > other.dist;
    }
};

// 无权图最短路，起点 s，距离写入 dist[]。
void bfs(long long dist[], int s) {
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

// 等差数列求和：l + (l+1) + ... + r。
long long range_sum(long long l, long long r) {
    return (l + r) * (r - l + 1) / 2;
}

// 从传送发生的那一刻算起，连续 x 次攻击的伤害总和。
// 伤害序列为 d, d-1, ..., 1, d, d-1, ...（每 d 次打出一个完整循环）。
long long teleport_cost(long long x) {
    long long full = x / d; // 完整循环个数
    long long rem = x % d;  // 末尾不足一个循环的项数
    // 每个完整循环的和是 1 + 2 + ... + d；
    // 剩余 rem 项是 d, d-1, ..., d-rem+1。
    return full * range_sum(1, d) + range_sum(d - rem + 1, d);
}

// 传送之前（Pang 停在 k）的带权最短路，同时把每个“第一次传送”的答案统计进来。
long long solve() {
    for (int i = 1; i <= n; i++) {
        dist_shou[i] = INF;
        vis[i] = false;
    }
    dist_shou[1] = 0;

    priority_queue<PQNode> pq;
    PQNode start;
    start.u = 1;
    start.dist = 0;
    pq.push(start);

    long long ans = INF;
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (dist_k[v] >= d) {
                // Shou 走到 v 后 dist(k, v) >= d，Pang 传送过来并打出 d 点伤害。
                // 此后 Pang 停在 v，Shou 沿最短路走向 n，剩余伤害用公式算出。
                long long cand = dist_shou[u] + teleport_cost(dist_n[v] + 1);
                if (cand < ans) {
                    ans = cand;
                }
            }
            else {
                // dist(k, v) < d，Pang 留在 k，这一秒伤害为 d - dist_k[v]。
                long long nd = dist_shou[u] + (d - dist_k[v]);
                if (nd < dist_shou[v]) {
                    dist_shou[v] = nd;
                    PQNode node;
                    node.u = v;
                    node.dist = nd;
                    pq.push(node);
                }
            }
        }
    }

    // 一次传送都没发生就走到 n 的情况。
    if (dist_shou[n] < ans) {
        ans = dist_shou[n];
    }
    return ans;
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

    bfs(dist_k, k);
    bfs(dist_n, n);
    cout << solve() << "\n";

    return 0;
}
