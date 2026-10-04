/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:29
 * update_at: 2026-10-04 23:29
 */

#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;

// col_pref[c][t] 表示第 c 列前 t 行之和（列和行都从 1 开始编号）
// 于是第 c 列在行区间 [i, j) 上的和 = col_pref[c][j] - col_pref[c][i]
ll col_pref[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            ll x;
            cin >> x;
            col_pref[c][r] = col_pref[c][r - 1] + x;
        }
    }

    // 答案初值取一个真实单格和，保证矩阵全为负数时也能返回最大单格而不是 0
    ll ans = col_pref[1][1];

    // 枚举上下边界 i, j（行区间 [i, j) 非空），把二维压成一维
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // 对该行区间下"每列的和"这一维数组跑 Kadane
            // acc 表示以当前列为右端点的最大非空子段和
            ll acc = col_pref[1][j] - col_pref[1][i];
            ll best = acc;
            for (int c = 2; c <= n; c++) {
                ll col_sum = col_pref[c][j] - col_pref[c][i];
                // 要么从本列重新开始，要么接在以上一列为右端点的最优子段后面
                acc = max(col_sum, acc + col_sum);
                best = max(best, acc);
            }
            ans = max(ans, best);
        }
    }

    cout << ans << endl;
    return 0;
}
