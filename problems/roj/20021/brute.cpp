/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按题意把每个 3x3 小矩阵存成 9 个字符的 string，用 set<string> 去重。
// string 比较和 set 操作开销大，只适合 n,m 很小的数据（这里按 n,m <= 30 使用）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;   // 小数据：n,m <= 30

int n, m;
string g[MAXN];      // 像素矩阵的每一行
set<string> blocks;  // 收集所有不同的 3x3 小矩阵，自动去重

// 提取左上角为 (x, y) 的 3x3 小矩阵，按行优先拼成 9 个字符的字符串。
string get_block(int x, int y) {
    string s;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s.push_back(g[x + i][y + j]);
        }
    }
    return s;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> g[i];

    blocks.clear();
    // 横向 n/3 块、纵向 m/3 块；块 (bi, bj) 的左上角是 (bi*3, bj*3)。
    for (int bi = 0; bi < n / 3; bi++) {
        for (int bj = 0; bj < m / 3; bj++) {
            blocks.insert(get_block(bi * 3, bj * 3));
        }
    }
    cout << blocks.size() << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}