/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:49
 * update_at: 2026-10-04 21:49
 */

// 牛半仙的妹子gcd：求 sum_{i,j,k=1}^{n} gcd(i, j, k)
// 属性值序列 (n, n-1, ..., 1) 是 1..n 的排列，所以答案就是上述三重 gcd 和。
#include <cstdio>

typedef long long ll;

const int MAXN = 1005;

int n;
ll cnt[MAXN]; // cnt[g] = 1 <= i, j <= n 中 gcd(i, j) 恰好等于 g 的数对个数
ll sum[MAXN]; // sum[g] = 第三个数 k 取 1..n 时 gcd(g, k) 的和

// 求 a, b 的最大公约数
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &n);

    // 第一段：枚举全部数对 (i, j)，按前两数的 gcd 分桶计数
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cnt[gcd(i, j)]++;

    // 第二段：gcd(i,j,k) = gcd(gcd(i,j), k)，对每个 g 求第三维的贡献和 S(g)
    for (int g = 1; g <= n; g++)
        for (int k = 1; k <= n; k++)
            sum[g] += gcd(g, k);

    // 结算：每个数对 (i,j) 落在唯一的桶 cnt[gcd(i,j)] 里，贡献是 sum[gcd(i,j)]
    ll ans = 0;
    for (int g = 1; g <= n; g++)
        ans += cnt[g] * sum[g];

    printf("%lld\n", ans);
    return 0;
}
