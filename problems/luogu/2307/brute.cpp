/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 11:30
 * update_at: 2026-08-05 11:30
 */
// brute.cpp：小数据暴力解，对每组数据建邻接表，
// 用 BFS 判连通 + DFS 判环，与并查集解法独立实现。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> g[MAXN];    // 邻接表
bool appear[MAXN];
bool vis[MAXN];
vector<int> nodes;      // 本组出现的所有节点

// BFS：从 start 出发，统计能到达的节点数
int bfs_count(int start) {
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                cnt++;
                q.push(v);
            }
        }
    }
    return cnt;
}

// DFS 判环：从 u 出发，若访问到已在当前栈中的点则有环
bool dfs_cycle(int u, int parent) {
    vis[u] = true;
    for (int v : g[u]) {
        if (v == parent) continue;   // 忽略回父亲的边（无向图）
        if (vis[v]) return true;     // 访问到已访问过的点：有环
        if (dfs_cycle(v, u)) return true;
    }
    return false;
}

// 清空本组数据的邻接表和标记
void clear_all() {
    for (int x : nodes) {
        g[x].clear();
        appear[x] = false;
    }
    nodes.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int u, v;
    while (cin >> u >> v) {
        if (u == -1 && v == -1) break;
        if (u == 0 && v == 0) {
            bool ok = true;
            if (!nodes.empty()) {
                // 判环
                memset(vis, 0, sizeof(vis));
                if (dfs_cycle(nodes[0], -1)) ok = false;
                // 判连通：BFS 能到达的节点数 == 出现节点总数
                int reach = bfs_count(nodes[0]);
                if (reach != (int)nodes.size()) ok = false;
            }
            cout << (ok ? 1 : 0) << '\n';
            clear_all();
            continue;
        }

        if (!appear[u]) { appear[u] = true; nodes.push_back(u); }
        if (!appear[v]) { appear[v] = true; nodes.push_back(v); }
        g[u].push_back(v);
        g[v].push_back(u);
    }

    return 0;
}
