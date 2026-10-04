/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll MAXN = 105; // 题目为 N x N 矩阵，N 一般不超过 100，留一点余量

ll n;
ll a[MAXN][MAXN]; // 原始矩阵
ll col[MAXN];     // 枚举上下边界时，每一列在 [top, bottom] 内的累加和

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (ll i = 0; i < n; ++i)
        for (ll j = 0; j < n; ++j)
            std::cin >> a[i][j];

    ll ans = a[0][0]; // 答案初始化为某个元素，保证子矩阵非空

    // 枚举子矩阵的上边界 top
    for (ll top = 0; top < n; ++top) {
        for (ll j = 0; j < n; ++j) col[j] = 0; // 每换一个上边界，列和清零

        // 枚举子矩阵的下边界 bottom，同时把第 bottom 行累加进列和
        for (ll bottom = top; bottom < n; ++bottom) {
            for (ll j = 0; j < n; ++j)
                col[j] += a[bottom][j];

            // 对一维数组 col 做 Kadane 求最大子段和
            ll cur = col[0];
            ll best = col[0];
            for (ll j = 1; j < n; ++j) {
                cur = std::max(col[j], cur + col[j]);
                best = std::max(best, cur);
            }
            ans = std::max(ans, best);
        }
    }

    std::cout << ans << "\n";
    return 0;
}
