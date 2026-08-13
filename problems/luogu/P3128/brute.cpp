/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:30
 */
// brute.cpp：小数据暴力解，每条路径用 BFS 找出整条路径，再沿路逐点加 1，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

int n, k;
vector<int> g[MAXN];
int pre_node[MAXN];   // BFS 中记录每个点是从哪个点走来的，用于还原路径
int count_node[MAXN]; // 每个点被经过的次数

// 把路径 start -> target 上所有点（含端点）的经过次数加 1。
void mark_path(int start, int target) {
    // BFS 找从 start 到 target 的一条路径，记录每个点的前驱。
    for (int i = 1; i <= n; i++) pre_node[i] = -1;
    queue<int> que;
    que.push(start);
    pre_node[start] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == target) break;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (pre_node[v] == -1) {
                pre_node[v] = u;
                que.push(v);
            }
        }
    }

    // 从 target 沿前驱一路走回 start，逐点加 1。
    int x = target;
    while (x != 0) {
        count_node[x]++;
        if (x == start) break;
        x = pre_node[x];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        mark_path(u, v);
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (answer < count_node[i]) answer = count_node[i];
    }
    cout << answer << '\n';
    return 0;
}
