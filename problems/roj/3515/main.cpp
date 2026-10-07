/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:40
 * update_at: 2026-10-06 12:40
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 25;        // 列数上限

ll f[MAXM];                 // 滚动数组：当前行到第 j 列的路径数
bool blocked[MAXM][MAXM];   // 马的控制点标记

// 马的 8 个跳跃位移（“马走日”）
const int dx[8] = {1, 2, -1, -2, 1, 2, -1, -2};
const int dy[8] = {2, 1, 2, 1, -2, -1, -2, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, hx, hy;
    cin >> n >> m >> hx >> hy;

    // 标记马所在点及 8 个跳跃落点
    blocked[hx][hy] = true;
    for (int k = 0; k < 8; k++) {
        ll nx = hx + dx[k];
        ll ny = hy + dy[k];
        if (0 <= nx && nx <= n && 0 <= ny && ny <= m) {
            blocked[nx][ny] = true;
        }
    }

    // 起点被控制则答案自然为 0
    f[0] = blocked[0][0] ? 0 : 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (blocked[i][j]) {
                f[j] = 0;           // 控制点不可通行
            } else if (j > 0) {
                f[j] += f[j - 1];   // 上面来 + 左边来
            }
            // j == 0 且非控制点时保留上一行传下来的 f[0]
        }
    }

    cout << f[m] << endl;
    return 0;
}
