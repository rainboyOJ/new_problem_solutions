/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 11:10
 * update_at: 2026-08-04 11:10
 */

/* P2196 [NOIP 1996 提高组] 挖地雷 */
/* DAG 最长路 DP：地窖编号天然是拓扑序，f[i] = 以 i 结尾的最大地雷数。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];                  // a[i]：第 i 个地窖的地雷数
int conn[MAXN][MAXN];         // conn[i][j] = 1 表示 i 到 j 有路径（i < j）
int f[MAXN];                  // f[i]：挖到地窖 i 结束能挖到的最大地雷数
int pre[MAXN];                // pre[i]：最优方案中地窖 i 是从哪个地窖来的（路径还原）

int rcd[MAXN];                // 最优路径（逆序存放）
int cnt;                      // 最优路径长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    // 输入只给 i -> j（i < j）的连通关系
    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> conn[i][j];

    // 边界：从地窖 i 开始挖，至少能挖到 a[i] 个
    for (int i = 1; i <= n; i++)
        f[i] = a[i];

    // 编号小的在前，编号大的在后，天然是拓扑序，按编号顺序递推即可
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (conn[j][i] == 1 && f[i] < f[j] + a[i]) {
                f[i] = f[j] + a[i];
                pre[i] = j;   // 记录最优前驱，用于路径还原
            }
        }
    }

    // 答案 = 所有 f[i] 的最大值，并记录终点下标
    int ans = 0, idx = 1;
    for (int i = 1; i <= n; i++) {
        if (ans < f[i]) {
            idx = i;
            ans = f[i];
        }
    }

    // 从终点沿 pre 链回溯，得到逆序路径
    for (int i = idx; i != 0; i = pre[i])
        rcd[++cnt] = i;

    // 逆序输出还原为正序
    for (int i = cnt; i >= 1; i--)
        cout << rcd[i] << " ";
    cout << '\n' << ans << '\n';

    return 0;
}
