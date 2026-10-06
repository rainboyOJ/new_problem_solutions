/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:00
 * update_at: 2026-10-06 16:00
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
ll c[MAXN]; // c[i] 表示第 i 个兵营的工兵数（包含天降神兵后的数量）

// 气势差最大约 c_i * |m-i| * n ≈ 2e19，超过 long long 上限，故用 __int128 保存。
// 返回 __int128 的绝对值。
__int128 i128_abs(__int128 x) {
    if (x < 0) return -x;
    return x;
}

// 返回 count 位工兵落在 pos 号兵营产生的带符号气势：龙方为正、虎方为负。
__int128 signed_momentum(ll count, ll pos, ll m) {
    __int128 cnt = count;
    return cnt * (m - pos);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
    }
    ll m, p1, s1, s2;
    scanf("%lld %lld %lld %lld", &m, &p1, &s1, &s2);

    c[p1] += s1; // 天降神兵：先在 p1 号兵营补上 s1 人

    // delta = 龙方气势 - 虎方气势 = sum c[i] * (m - i)
    // p < m 时为正（龙），p > m 时为负（虎），p = m 时恰为 0
    __int128 delta = 0;
    for (int i = 1; i <= n; i++) {
        delta += signed_momentum(c[i], i, m);
    }

    // 枚举投放位置，取使 |delta + s2*(m-p)| 最小的最小编号；
    // 初值取 p2 = m（相当于不改变气势），并保证并列时保留更左的编号
    ll ans = m;
    __int128 best = i128_abs(delta);
    for (int p = 1; p <= n; p++) {
        __int128 cur = i128_abs(delta + signed_momentum(s2, p, m));
        if (cur < best) {
            best = cur;
            ans = p;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
