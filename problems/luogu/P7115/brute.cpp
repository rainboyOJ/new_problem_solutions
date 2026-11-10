/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:35
 * update_at: 2026-11-10 23:35
 */
// brute.cpp：执行输入与 main.cpp 方案的校验器
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> col(n + 2);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            col[i].push_back(x);
        }
    }

    int k;
    if (!(cin >> k)) return 0;
    if (k > 820000) {
        cout << "FAIL: too many steps\n";
        return 0;
    }

    for (int step = 1; step <= k; ++step) {
        int u, v;
        cin >> u >> v;
        if (col[u].empty() || col[v].size() >= static_cast<size_t>(m)) {
            cout << "FAIL: invalid move\n";
            return 0;
        }
        col[v].push_back(col[u].back());
        col[u].pop_back();
    }

    // 检查是否恰好有 n 根满柱且每根单色
    int full_single = 0;
    for (int i = 1; i <= n + 1; ++i) {
        if (col[i].empty()) continue;
        if (col[i].size() != static_cast<size_t>(m)) {
            cout << "FAIL: column size not m\n";
            return 0;
        }
        int c = col[i][0];
        for (int x : col[i]) {
            if (x != c) {
                cout << "FAIL: column not monochromatic\n";
                return 0;
            }
        }
        full_single++;
    }

    if (full_single == n) {
        cout << "OK\n";
    } else {
        cout << "FAIL: not all full\n";
    }

    return 0;
}
