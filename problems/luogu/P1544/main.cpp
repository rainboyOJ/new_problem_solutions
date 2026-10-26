/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:40
 * update_at: 2026-10-26 16:36
 */
// main.cpp：数字金字塔 + 三倍次数的三维 DP，滚动数组实现。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100 + 5;
const ll NEG_INF = LLONG_MIN / 4; // 不可达状态的哨兵，加一个格子权值也不会溢出

ll n, k;                // 行数、乘 3 次数上限（读入后截断成 k' = min(k, n)）
ll a[MAXN][MAXN];       // 数字金字塔，a[i][j] 是第 i 行第 j 个数
ll dp[2][MAXN][MAXN];   // 滚动数组：dp[cur][j][c] = 走到 (当前行, j) 且已乘 3 共 c 次的最大得分

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    // 一条路径只经过 n 个格子，用不完 n 次以上的乘 3 机会，截断后状态数有限。
    if (k > n) {
        k = n;
    }

    int pre = 0; // 上一行对应的层
    int cur = 1; // 当前行对应的层
    // 整张滚动数组先全部置成 NEG_INF，避免读到上一行不存在的列时拿到旧值
    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j <= n; j++) {
            for (ll c = 0; c <= k; c++) {
                dp[i][j][c] = NEG_INF;
            }
        }
    }
    dp[pre][1][0] = a[1][1]; // 起点 (1,1)，不乘 3
    if (k >= 1) {
        dp[pre][1][1] = a[1][1] * 3; // 起点乘 3
    }

    for (ll i = 2; i <= n; i++) {
        // 当前行会在第 i 列被写入，但只会读第 1..i 列，多清到 n 防止读到旧行残留
        for (ll j = 0; j <= n; j++) {
            for (ll c = 0; c <= k; c++) {
                dp[cur][j][c] = NEG_INF;
            }
        }
        for (ll j = 1; j <= i; j++) {
            for (ll c = 0; c <= k; c++) {
                // 先从两个前驱里取较大值，再加当前格的贡献
                ll best = dp[pre][j][c]; // 前驱 (i-1, j)，即从左上方下来
                if (dp[pre][j - 1][c] > best) {
                    best = dp[pre][j - 1][c]; // 前驱 (i-1, j-1)，即从右上方下来
                }
                if (best != NEG_INF) {
                    dp[cur][j][c] = best + a[i][j]; // 当前格不乘 3
                }
                if (c >= 1) {
                    // 当前格乘 3：前驱要求上一行恰好用了 c-1 次
                    ll best2 = dp[pre][j][c - 1];
                    if (dp[pre][j - 1][c - 1] > best2) {
                        best2 = dp[pre][j - 1][c - 1];
                    }
                    if (best2 != NEG_INF) {
                        if (best2 + a[i][j] * 3 > dp[cur][j][c]) {
                            dp[cur][j][c] = best2 + a[i][j] * 3;
                        }
                    }
                }
            }
        }
        swap(pre, cur); // 当前行算完，滚动到下一行
    }

    // 答案：最后一行任意一列、任意已用次数（允许用不满 k 次，dp 值随 c 非降不保证，取 max）
    ll ans = NEG_INF;
    for (ll j = 1; j <= n; j++) {
        for (ll c = 0; c <= k; c++) {
            if (dp[pre][j][c] > ans) {
                ans = dp[pre][j][c];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
