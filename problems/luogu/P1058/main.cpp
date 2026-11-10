/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:05
 * update_at: 2026-11-11 01:05
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAXM = 55;
const int MAXN = 55;
const int MAXDIM = 1005;

int h[MAXM][MAXN];
char canvas[MAXDIM][MAXDIM];

// 6行7列积木模型，'.' 表示透明区域，不进行覆盖
const string block[6] = {
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

    int max_x = 0;
    int max_y = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> h[i][j];
            if (h[i][j] > 0) {
                // 左下角基准坐标 (X, Y)
                int x = (j - 1) * 4 + (m - i) * 2;
                int y = (m - i) * 2 + (h[i][j] - 1) * 3;
                max_x = max(max_x, x + 6);
                max_y = max(max_y, y + 5);
            }
        }
    }

    int total_rows = max_y + 1;
    int total_cols = max_x + 1;

    // 初始化画布背景为 '.'
    for (int r = 0; r < total_rows; ++r) {
        for (int c = 0; c < total_cols; ++c) {
            canvas[r][c] = '.';
        }
    }

    // 画家算法：由远及近 (i: 1 -> m)、由左至右 (j: 1 -> n)、自底向上 (k: 1 -> h[i][j])
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= h[i][j]; ++k) {
                int x = (j - 1) * 4 + (m - i) * 2;
                int y = (m - i) * 2 + (k - 1) * 3;

                // 积木顶部在画布中的行下标
                int top_row = total_rows - 1 - (y + 5);

                for (int dr = 0; dr < 6; ++dr) {
                    for (int dc = 0; dc < 7; ++dc) {
                        char ch = block[dr][dc];
                        if (ch != '.') {
                            canvas[top_row + dr][x + dc] = ch;
                        }
                    }
                }
            }
        }
    }

    // 输出最终画布
    for (int r = 0; r < total_rows; ++r) {
        for (int c = 0; c < total_cols; ++c) {
            cout << canvas[r][c];
        }
        cout << "\n";
    }

    return 0;
}
