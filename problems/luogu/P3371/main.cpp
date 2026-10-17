/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * update_at: 2026-10-17 15:31
 */
// P3371 【模板】单源最短路径（弱化版）
// SPFA：dis[v] 被更新后把 v 重新入队，重复松弛直到队列为空。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
const long long INF = (1LL << 62);
const long long UNREACH = 2147483647LL; // 题目要求：不可达输出 2^31-1

struct edge {
    int to;
    long long w;
};

vector<edge> g[maxn];
long long dis[maxn];
int cnt[maxn];       // 当前 dis 对应的历史路径的边数，不是更新次数
bool in_queue[maxn]; // 当前是否在队列中，出队后必须清除

void init_graph(int n) {
    for (int u = 1; u <= n; ++u) g[u].clear();
}

void add_edge(int u, int v, long long w) {
    g[u].push_back({v, w});
}

// 本题 w >= 0，一定没有负环；返回 false 只是防御性写法。
bool spfa(int n, int s) {
    fill(dis + 1, dis + n + 1, INF);
    fill(cnt + 1, cnt + n + 1, 0);
    fill(in_queue + 1, in_queue + n + 1, false);
    queue<int> q; // 局部队列保证重复调用时没有上次留下的点

    dis[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const auto& e : g[u]) {
            int v = e.to;
            long long candidate = dis[u] + e.w; // 入队点一定可达
            if (candidate >= dis[v]) continue;

            dis[v] = candidate;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] >= n) return false; // 从 s 可达的负环

            // 即使 v 已在队列中，也必须先更新 dis 和 cnt。
            if (!in_queue[v]) {
                q.push(v);
                in_queue[v] = true;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;

    init_graph(n);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    spfa(n, s);

    for (int v = 1; v <= n; ++v) {
        if (v > 1) cout << ' ';
        if (dis[v] == INF) cout << UNREACH;
        else cout << dis[v];
    }
    cout << '\n';

    return 0;
}
