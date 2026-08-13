/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:28
 * update_at: 2026-08-13 13:32
 */
/* P1101 单词方阵 */
/* 枚举每个起点与 8 个方向，检查 7 个连续字符是否构成 yizhong。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
char g[MAXN][MAXN];    // 字母方阵
int keep[MAXN][MAXN];  // keep[i][j] = 1 表示该字符属于某个单词
const char word[] = "yizhong";
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// 判断以 (x,y) 为起点、沿方向 d 的 7 个字符是否正好是 yizhong。
bool match(int x, int y, int d) {
    for (int step = 0; step < 7; step++) {
        int nx = x + dx[d] * step;
        int ny = y + dy[d] * step;
        if (nx < 1 || nx > n || ny < 1 || ny > n) {
            return false;  // 超出方阵边界
        }
        if (g[nx][ny] != word[step]) {
            return false;  // 字符不匹配
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }

    // 枚举每个起点和 8 个方向
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (g[x][y] != 'y') {
                continue;  // 首字母不是 y，不可能成为单词起点
            }
            for (int d = 0; d < 8; d++) {
                if (match(x, y, d)) {
                    // 匹配成功，标记这 7 个位置（不同单词可交叉共用）
                    for (int step = 0; step < 7; step++) {
                        int nx = x + dx[d] * step;
                        int ny = y + dy[d] * step;
                        keep[nx][ny] = 1;
                    }
                }
            }
        }
    }

    // 属于单词的字符保留原样，其余输出 *
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (keep[i][j]) {
                cout << g[i][j];
            } else {
                cout << '*';
            }
        }
        cout << '\n';
    }

    return 0;
}
