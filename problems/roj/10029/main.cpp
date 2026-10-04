/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:16
 * update_at: 2026-10-04 22:16
 */
#include <cstdio>

typedef long long ll;

const ll MOD = 1e9 + 7;
const int MAXN = 1005;

ll f[MAXN]; // f[i] 表示值 i 的回文拆分数（mod 1e9+7）

int main() {
    ll n;
    scanf("%lld", &n);

    // 由归纳定义推出：
    // 基础型恒有 1 个，A+A 型贡献 f(n/2)（n 为偶数），
    // A+x+A 型贡献 sum_{a<=floor((n-1)/2)} f(a)，用前缀和化简后得
    // 关键恒等式 f(2m)=f(2m+1)=F(m)，等价于下面两条递推：
    // 奇数项抄前一项，偶数项 = 前一项 + 半值项。
    f[1] = 1;
    for (ll k = 2; k <= n; ++k) {
        if (k % 2 == 1)
            f[k] = f[k - 1];
        else
            f[k] = (f[k - 1] + f[k / 2]) % MOD;
    }

    printf("%lld\n", f[n]);
    return 0;
}
