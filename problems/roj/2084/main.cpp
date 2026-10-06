/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:16
 * update_at: 2026-10-06 12:16
 */

// main.cpp：校园网。
// 把互相可达的学校缩成一个强连通分量后，答案只与缩点 DAG 的度数有关：
// 子任务 A 是入度为 0 的分量个数，子任务 B 是入度为 0 与出度为 0 的分量个数的较大值。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll n;
vector<int> g[MAXN];   // g[u] = 原图中学校 u 能分发到的学校
vector<int> rg[MAXN];  // rg[v] = 原图中能分发到学校 v 的学校（反图）
int comp[MAXN];        // comp[v] = 学校 v 所属的强连通分量编号（-1 表示还没染色）
bool seen[MAXN];       // 第一遍 Kosaraju 的访问标记
int order[MAXN];       // 第一遍 Kosaraju 得到的逆后序
int order_cnt;
bool has_in[MAXN];     // has_in[c] = 分量 c 是否存在跨分量的入边
bool has_out[MAXN];    // has_out[c] = 分量 c 是否存在跨分量的出边

// 第一遍 Kosaraju：在反图上 DFS，按离开的先后次序记录逆后序。
void dfs_order(int u) {
    seen[u] = true;
    for (size_t i = 0; i < rg[u].size(); i++) {
        int v = rg[u][i];
        if (!seen[v]) {
            dfs_order(v);
        }
    }
    order[++order_cnt] = u;
}

// 第二遍 Kosaraju：按逆后序在原图上扩散，同一轮能染到的点属于同一个强连通分量。
void dfs_color(int u, int cid) {
    comp[u] = cid;
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (comp[v] == -1) {
            dfs_color(v, cid);
        }
    }
}

void read_input() {
    cin >> n;
    for (int u = 1; u <= n; u++) {
        while (true) {
            ll v;
            cin >> v;
            if (v == 0) {
                break;
            }
            g[u].push_back(v);
            rg[v].push_back(u); // 正反图同时建好，供两遍 DFS 使用
        }
    }
}

void solve() {
    // 第一遍：在反图上求逆后序。
    for (int u = 1; u <= n; u++) {
        if (!seen[u]) {
            dfs_order(u);
        }
    }

    // 第二遍：按逆后序在原图上染色，得到所有强连通分量。
    for (int i = 1; i <= n; i++) {
        comp[i] = -1;
    }
    int total = 0;
    for (int i = n; i >= 1; i--) {
        int u = order[i];
        if (comp[u] == -1) {
            dfs_color(u, total);
            total++; // 分量编号从 0 连续排到 total-1
        }
    }

    // 缩点后只统计分量之间的边，分量内部的边对可达性没有贡献。
    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (comp[u] != comp[v]) {
                has_out[comp[u]] = true;
                has_in[comp[v]] = true;
            }
        }
    }

    int sources = 0; // 入度为 0 的分量个数
    int sinks = 0;   // 出度为 0 的分量个数
    for (int c = 0; c < total; c++) {
        if (!has_in[c]) {
            sources++;
        }
        if (!has_out[c]) {
            sinks++;
        }
    }

    cout << sources << "\n"; // 子任务 A：每个源分量各发一份
    // 子任务 B：只有一个分量时图本身已强连通，否则为源、汇个数的较大值。
    if (total == 1) {
        cout << 0 << "\n";
    } else {
        cout << max(sources, sinks) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
