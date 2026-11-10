/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:37
 * update_at: 2026-11-10 22:37
 */

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// 方格最大边长 N <= 9
const int MAXN = 12;

// 方格上的数字，a[x][y] 表示坐标 (x, y) 处的权值
int a[MAXN][MAXN];

// f[k][i][r] 表示两个人同时走了若干步，当前步数和 x+y = k
// 且第一个人在第 i 行（列为 k-i），第二个人在第 r 行（列为 k-r）时的最大取得数字和
int f[MAXN * 2][MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int x, y, v;
    while (cin >> x >> y >> v && (x || y || v)) {
        a[x][y] = v;
    }

    // 步数和 k 从 2（起点 1+1）到 2n（终点 n+n）
    for (int k = 2; k <= 2 * n; ++k) {
        // 枚举两个人所在的行 i 和 r
        for (int i = 1; i <= n; ++i) {
            int j = k - i; // 第一个人所在的列
            if (j < 1 || j > n) continue;

            for (int r = 1; r <= n; ++r) {
                int c = k - r; // 第二个人所在的列
                if (c < 1 || c > n) continue;

                // 计算当前格子取得的权值
                int current_value = 0;
                if (i == r) {
                    // 两人到达同一格子，权值只能取一次
                    current_value = a[i][j];
                } else {
                    // 两人在不同格子，各自取走当前格子的权值
                    current_value = a[i][j] + a[r][c];
                }

                // 枚举两人上一步的来向：来自上边（行-1）还是左边（列-1，即行不变）
                // 1. 两人都从上方来：(i-1, r-1)
                // 2. 第一个人从上方，第二个人从左方：(i-1, r)
                // 3. 第一个人从左方，第二个人从上方：(i, r-1)
                // 4. 两人都从左方来：(i, r)
                int max_prev = f[k - 1][i - 1][r - 1];
                max_prev = max(max_prev, f[k - 1][i - 1][r]);
                max_prev = max(max_prev, f[k - 1][i][r - 1]);
                max_prev = max(max_prev, f[k - 1][i][r]);

                f[k][i][r] = max_prev + current_value;
            }
        }
    }

    // 终点时两人都走到 (n, n)，步数和为 2n，第一条路径行号为 n，第二条路径行号为 n
    cout << f[2 * n][n][n] << "\n";

    return 0;
}
