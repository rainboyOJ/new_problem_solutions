/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:05
 * update_at: 2026-11-11 01:05
 */

// brute.cpp：小数据验证基线
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const string pat[6] = {
    "..+---+",
    "./   /|",
    "+---+ |",
    "|   | +",
    "|   |/.",
    "+---+.."
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;
    vector<vector<int>> h(m, vector<int>(n));

    int max_r = 0, max_c = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> h[i][j];
            int x = j * 4 + (m - 1 - i) * 2;
            int y = (m - 1 - i) * 2 + (h[i][j] - 1) * 3;
            max_c = max(max_c, x + 6);
            max_r = max(max_r, y + 5);
        }
    }

    int H = max_r + 1, W = max_c + 1;
    vector<string> g(H, string(W, '.'));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < h[i][j]; ++k) {
                int x = j * 4 + (m - 1 - i) * 2;
                int y = (m - 1 - i) * 2 + k * 3;
                int top = H - 1 - (y + 5);
                for (int r = 0; r < 6; ++r) {
                    for (int c = 0; c < 7; ++c) {
                        if (pat[r][c] != '.') {
                            g[top + r][x + c] = pat[r][c];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < H; ++i) cout << g[i] << "\n";
    return 0;
}
