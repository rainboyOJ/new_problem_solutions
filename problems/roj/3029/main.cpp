/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:20
 * update_at: 2026-10-06 11:22
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

ll a[MAXN][MAXN]; // 原矩阵
ll s[MAXN][MAXN]; // s[i][j] 表示前 i 行第 j 列的元素和（列前缀和）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    // 读入矩阵，同时构建列前缀和：s[i][j] = sum_{r=0}^{i-1} a[r][j]
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            s[i][j] = s[i - 1][j] + a[i][j];
        }
    }

    ll ans = a[1][0]; // 初始答案，至少取一个元素
    // 枚举行界 [u, d]
    for (int u = 1; u <= n; u++) {
        for (int d = u; d <= n; d++) {
            ll cur = 0; // 以当前列结尾的最大子段和
            for (int c = 0; c < n; c++) {
                ll colsum = s[d][c] - s[u - 1][c]; // 第 c 列在行 [u, d] 的竖条和
                // Kadane：若 cur < 0 则丢弃，从当前列重新开始
                if (cur < 0) cur = colsum;
                else cur += colsum;
                if (cur > ans) ans = cur;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
