/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 15:30
 * update_at: 2026-11-12 15:30
 */
// brute.cpp：小图暴力解法，用于辅助对拍
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 20;
vector<int> g[maxn];
string s;
int n, m;

int color[maxn]; // 0: unvisited, 1: visiting, 2: visited
bool has_cycle = false;

void check_cycle(int u) {
    color[u] = 1;
    for (int v : g[u]) {
        if (color[v] == 1) {
            has_cycle = true;
            return;
        }
        if (color[v] == 0) {
            check_cycle(v);
            if (has_cycle) return;
        }
    }
    color[u] = 2;
}

int global_max_cnt = 0;
int cur_cnt[26];

void dfs_path(int u) {
    int c = s[u - 1] - 'a';
    cur_cnt[c]++;
    global_max_cnt = max(global_max_cnt, cur_cnt[c]);

    for (int v : g[u]) {
        dfs_path(v);
    }

    cur_cnt[c]--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    cin >> s;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    // 1. 判环
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            check_cycle(i);
            if (has_cycle) {
                cout << -1 << "\n";
                return 0;
            }
        }
    }

    // 2. 枚举所有路径
    for (int i = 1; i <= n; ++i) {
        dfs_path(i);
    }

    cout << global_max_cnt << "\n";
    return 0;
}
