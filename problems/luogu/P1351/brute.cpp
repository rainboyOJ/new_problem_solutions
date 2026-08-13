/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:00
 */
// brute.cpp：小数据暴力解，枚举所有距离为 2 的有序点对（BFS 爬两层邻居实现），
// 用来理解题意并辅助对拍，只适合 n <= 30 的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n;
int w[MAXN];         // w[i] 表示点 i 的权值
vector<int> g[MAXN]; // 邻接表存树
int dis[MAXN];       // BFS 中每个点到起点 u 的距离，-1 表示未访问

long long total_sum; // 所有有序点对联合权值之和，最后对 10007 取模
int max_value;       // 联合权值最大值

// 从 u 出发 BFS 爬两层邻居，找出所有距离恰好为 2 的点 v：
// 每个 (u, v) 是一个距离为 2 的有序点对，贡献 w[u] * w[v]。
void bfs_collect(int u) {
    memset(dis, -1, sizeof(dis));
    queue<int> q;
    dis[u] = 0;
    q.push(u);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < (int)g[x].size(); i++) {
            int v = g[x][i];
            if (dis[v] != -1) continue; // 已经访问过
            dis[v] = dis[x] + 1;
            if (dis[v] < 2) q.push(v); // 距离 2 的点不需要再向外扩展
        }
    }

    for (int v = 1; v <= n; v++) {
        if (dis[v] == 2) {
            int value = w[u] * w[v];
            total_sum += value;
            if (value > max_value) max_value = value;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> w[i];

    // 枚举每个起点，BFS 找它所有距离为 2 的点，逐对统计。
    for (int u = 1; u <= n; u++) {
        bfs_collect(u);
    }

    cout << max_value << ' ' << total_sum % 10007 << '\n';
    return 0;
}
