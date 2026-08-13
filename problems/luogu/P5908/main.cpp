/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:27
 * update_at: 2026-08-12 22:27
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, d;
vector<int> g[MAXN]; // g[u] 保存与 u 相邻的所有点（邻接表）
int dist[MAXN];      // dist[u] 表示 u 到 1 号点的距离，-1 表示还没访问过
int ans;             // 可以拜访的企鹅数量（不含 1 号点本身）

// 从 1 号点 BFS，边权全为 1，距离恰好为 d 的点不再扩展。
void bfs() {
    queue<int> q;
    memset(dist, -1, sizeof(dist));
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // 距离已经是 d 的点，再走一步就超过 d，不需要扩展。
        if (dist[u] == d) continue;

        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (dist[v] != -1) continue; // v 已经被访问过，跳过

            dist[v] = dist[u] + 1;
            ans++; // 每发现一个新点，就多一只可以拜访的企鹅
            q.push(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs();
    cout << ans << endl;

    return 0;
}
