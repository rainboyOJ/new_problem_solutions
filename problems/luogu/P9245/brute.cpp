/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:38
 * update_at: 2026-10-03 11:38
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接照抄题面的定义：
//   对每一个要跳过的景点 A[i]，把剩下的 K-1 个景点按原顺序排成新线路，
//   再一段一段地数时间——对其中每一对相邻景点 (u, v) 都单独做一次 BFS，
//   从 u 出发遍历整棵树算出到所有点的距离，取 dist[v] 就是这一段的时间。
// 每段路径都要重新搜一遍整棵树，复杂度约 O(K^2 * N)，
// 节点数稍大就会很慢，所以只适合小数据对拍。
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1005; // 暴力只跑小树
const int MAXM = 2005;

int n, k;
int a[MAXN];    // 原定游览线路 A[1..K]
int keep[MAXN]; // 跳过某个景点后剩下的游览顺序

// 链式前向星存树
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int wt[MAXM];

long long dist[MAXN]; // 本次 BFS 中，起点到每个点的路径长度；-1 表示还没访问
queue<int> q;   // BFS 队列

// 加一条无向边：u <-> v，花费时间 w。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    wt[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 求树上 u 到 v 的唯一路径长度：从 u 出发做一次 BFS。
long long path_len(int u, int v) {
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    while (!q.empty()) {
        q.pop();
    }

    dist[u] = 0;
    q.push(u);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i != 0; i = nxt[i]) {
            int y = to[i];
            if (dist[y] != -1) continue;
            dist[y] = dist[x] + wt[i];
            q.push(y);
        }
    }
    return dist[v];
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }
}

void solve() {
    for (int skip = 1; skip <= k; skip++) {
        // 把跳过 A[skip] 之后剩下的景点按原顺序收集到 keep[]。
        int cnt = 0;
        for (int i = 1; i <= k; i++) {
            if (i == skip) continue;
            cnt++;
            keep[cnt] = a[i];
        }

        // 一段一段地重新搜，累加新线路里每一对相邻景点之间的时间。
        long long total = 0;
        for (int i = 1; i <= cnt - 1; i++) {
            total += path_len(keep[i], keep[i + 1]);
        }

        if (skip != 1) cout << " ";
        cout << total;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
