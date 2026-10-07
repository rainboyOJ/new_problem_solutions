/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:50
 * update_at: 2026-10-05 08:50
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 205; // n 的上界（6 < n <= 200）
const int MAXK = 10;  // k 的上界（2 <= k <= 6）

ll f[MAXN][MAXK]; // f[i][j]：把 i 拆成 j 个正整数、不计顺序的方案数

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);

    // 边界：拆成 1 份只有一种（整块给它）；份数比总和还大则无解
    for (ll i = 0; i <= n; i++) {
        f[i][1] = 1;
        for (ll j = 2; j <= k; j++) {
            f[i][j] = 0; // 先默认无解，保证 i < j 时取到 0
            if (i >= j) {
                // 按最小值是否为 1 分类：
                // 最小值 = 1 → 删掉一个 1 → f[i-1][j-1]
                // 最小值 ≥ 2 → 每份减 1   → f[i-j][j]
                f[i][j] = f[i - 1][j - 1] + f[i - j][j];
            }
        }
    }

    printf("%lld\n", f[n][k]);
    return 0;
}
