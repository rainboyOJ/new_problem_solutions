/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 09:22
 * update_at: 2026-11-12 09:35
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。复杂度 O(T * N^2 * M)。
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 50000 + 50;
vector<int> a[maxn]; // 全局数组保存排列

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    for (int i = 0; i < n; ++i) {
        a[i].resize(m);
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            // 转为 0-based 数值，方便索引
            a[i][j]--;
        }
    }

    // 暴力枚举两两配对
    for (int i = 0; i < n; ++i) {
        int max_beauty = 0;
        for (int j = 0; j < n; ++j) {
            int cur_beauty = 0;
            for (int k = 0; k < m; ++k) {
                // 根据乘法定义：第 k 个位置的值是 a[j][a[i][k]]
                if (a[j][a[i][k]] == k) {
                    cur_beauty++;
                } else {
                    break;
                }
            }
            max_beauty = max(max_beauty, cur_beauty);
        }
        cout << max_beauty << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
