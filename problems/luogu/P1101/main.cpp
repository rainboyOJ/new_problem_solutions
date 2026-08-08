/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1101 单词方阵 */
/* 枚举每个格子作为起点和八个方向，检查是否为 yizhong。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
char g[MAXN][MAXN]; // 字母方阵
int mark[MAXN][MAXN]; // 标记属于单词的字符
char word[] = "yizhong";
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1);
    }

    // 枚举每个起点和八个方向
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int d = 0; d < 8; d++) {
                bool ok = true;
                // 检查 yizhong 是否沿方向 d 连续出现
                for (int step = 0; step < 7; step++) {
                    int nx = x + dx[d] * step;
                    int ny = y + dy[d] * step;
                    if (nx < 1 || nx > n || ny < 1 || ny > n) {
                        ok = false;
                        break;
                    }
                    if (g[nx][ny] != word[step]) {
                        ok = false;
                        break;
                    }
                }
                // 匹配成功，标记这七个位置
                if (ok) {
                    for (int step = 0; step < 7; step++) {
                        int nx = x + dx[d] * step;
                        int ny = y + dy[d] * step;
                        mark[nx][ny] = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mark[i][j])
                cout << g[i][j];
            else
                cout << '*';
        }
        cout << "\n";
    }
    return 0;
}
