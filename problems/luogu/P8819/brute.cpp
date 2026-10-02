/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:28
 * update_at: 2026-10-01 22:28
 */
// brute.cpp：小数据暴力解，逐条维护虫洞是否可用，每次指令后重新统计各据点出度。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 35;   // 暴力只服务小数据，n 取到 30 左右

int n, m, q;
bool exist_edge[MAXN][MAXN]; // exist_edge[u][v]：原图是否存在虫洞 u -> v
bool active_edge[MAXN][MAXN]; // active_edge[u][v]：虫洞 u -> v 当前是否可用

// 反攻时刻要求每个据点恰好有一条可用出边。
bool can_counterattack() {
    for (int u = 1; u <= n; u++) {
        int out_degree = 0;
        for (int v = 1; v <= n; v++) {
            if (active_edge[u][v]) {
                out_degree++;
            }
        }
        if (out_degree != 1) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        exist_edge[u][v] = true;
        active_edge[u][v] = true;
    }

    cin >> q;
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // 摧毁虫洞 u -> v。
            int u, v;
            cin >> u >> v;
            active_edge[u][v] = false;
        } else if (type == 2) {
            // 摧毁据点 v 的全部虫洞，即终点为 v 的那些。
            int v;
            cin >> v;
            for (int u = 1; u <= n; u++) {
                if (exist_edge[u][v]) {
                    active_edge[u][v] = false;
                }
            }
        } else if (type == 3) {
            // 修复虫洞 u -> v。
            int u, v;
            cin >> u >> v;
            if (exist_edge[u][v]) {
                active_edge[u][v] = true;
            }
        } else {
            // 修复据点 v 的全部虫洞。
            int v;
            cin >> v;
            for (int u = 1; u <= n; u++) {
                if (exist_edge[u][v]) {
                    active_edge[u][v] = true;
                }
            }
        }

        cout << (can_counterattack() ? "YES" : "NO") << '\n';
    }

    return 0;
}
