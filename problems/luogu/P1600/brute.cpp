/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:01
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：对每个玩家，先在树上 DFS 搜出 s -> t 的唯一路径，
// 再逐秒走过这条路径给每个点“打点”（记录到达时刻）；
// 最后对每个观察员 u 统计“到达时刻恰好等于 w[u]”的玩家数。
// 复杂度 O(m * n)，只适合 n 很小的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m;
vector<int> g[MAXN];
int w[MAXN];

int path[MAXN];          // 搜出的 s -> t 路径，按经过顺序存放
int path_len;            // 路径上点的个数
int arrive_time[MAXN];   // arrive_time[u]：当前玩家到达 u 的时刻，-1 表示没经过
int answer[MAXN];        // answer[u]：u 点观察员看到的人数

// 在树上搜 u -> target 的路径，找到后把整条路径填进 path[]。
// fa 是 u 的父亲，用来防止往回走。树上路径唯一，一定能找到。
bool dfs_find_path(int u, int fa, int target) {
    path[path_len++] = u;
    if (u == target) {
        return true;
    }
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        if (dfs_find_path(v, u, target)) {
            return true;
        }
    }
    path_len--;  // 这条分支没有 target，撤销 u
    return false;
}

// 模拟一个玩家从 s 跑到 t：逐时刻打点，再统计能被观察到的观察员。
void simulate_player(int s, int t) {
    path_len = 0;
    dfs_find_path(s, 0, t);  // path[0] = s, path[path_len-1] = t

    for (int u = 1; u <= n; u++) {
        arrive_time[u] = -1;
    }
    // 逐时刻打点：第 i 秒到达 path[i]。
    for (int i = 0; i < path_len; i++) {
        arrive_time[path[i]] = i;
    }

    // 对观察员计数：到达时刻恰好等于观察时刻 w[u]。
    for (int u = 1; u <= n; u++) {
        if (arrive_time[u] == w[u]) {
            answer[u]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= m; i++) {
        int s, t;
        cin >> s >> t;
        simulate_player(s, t);
    }

    for (int u = 1; u <= n; u++) {
        if (u > 1) {
            cout << ' ';
        }
        cout << answer[u];
    }
    cout << '\n';

    return 0;
}
