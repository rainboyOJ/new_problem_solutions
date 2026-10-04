/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:48
 * update_at: 2026-10-05 00:48
 */

#include <cstdio>

typedef long long ll;

const ll MAXN = 100005;

ll n, L;                // 序列长度、子段最短长度
ll a[MAXN];             // a[i]：第 i 个数放大 1000 倍后的值
ll prefix[MAXN];        // prefix[i]：b[1..i] 的前缀和，其中 b[k] = a[k] - x

// 判断：是否存在长度 >= L 的子段，其平均数 * 1000 >= x。
// 子段 [j+1, i] 平均数 >= x 等价于 sum(b[j+1..i]) >= 0，
// 即 prefix[i] >= prefix[j]；只需 prefix[i] 不小于 j in [0, i-L] 的最小前缀和。
bool check(ll x) {
    prefix[0] = 0;
    for (ll i = 1; i <= n; ++i)
        prefix[i] = prefix[i - 1] + a[i] - x; // 现场累加 b 的前缀和

    ll best = 0; // 窗口 [0, i-L] 内 prefix[j] 的最小值，随 i 右移单调维护
    for (ll i = L; i <= n; ++i) {
        if (prefix[i - L] < best)
            best = prefix[i - L]; // 新进入窗口的位置
        if (prefix[i] >= best)    // 找到平均数不小于 x 的子段
            return true;
    }
    return false;
}

int main() {
    scanf("%lld %lld", &n, &L);
    for (ll i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        a[i] *= 1000; // 整体放大 1000 倍，二分全程用整数，避免浮点误差
    }

    // 二分最大的 x：使存在长度 >= L 的子段平均数 * 1000 >= x
    ll lo = 0, hi = (ll)1e9; // 值域上界：每个数 <= 1e6，放大 1000 倍后 <= 1e9
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2; // 偏向中点，保证 lo 能推进
        if (check(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    printf("%lld\n", lo); // 最大可行 x 即答案的 1000 倍（下取整）
    return 0;
}
