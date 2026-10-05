/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:49
 * update_at: 2026-10-06 00:49
 */

// main.cpp：单点加 + 区间和，树状数组（Fenwick）模板题。
// tree[i] 管辖 (i - lowbit(i), i] 这一段的和。

#include <cstdio>

typedef long long ll;

const int MAXN = 1000005; // 真实数据 n 最大 1e6，比题面写的 1e5 大，按大的开

ll tree[MAXN]; // 树状数组，tree[i] = sum of (i - lowbit(i), i]
ll val[MAXN];  // 数列初值，val[i] 表示第 i 个数的初值
ll n, m;       // 数列长度、操作数

// 求前缀和 S(i) = a[1] + ... + a[i]，沿 i -= lowbit(i) 拆成 O(log n) 段
ll query_prefix(ll i) {
    ll sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= i & (-i);
    }
    return sum;
}

// 单点加：a[pos] += delta，沿 pos += lowbit(pos) 更新所有管辖 pos 的段
void update(ll pos, ll delta) {
    for (; pos <= n; pos += pos & (-pos))
        tree[pos] += delta;
}

int main() {
    scanf("%lld %lld", &n, &m);

    // 读入初值
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &val[i]);

    // O(n) 建树：正序把 tree[i] 的完整段和推给父结点 i + lowbit(i)
    for (ll i = 1; i <= n; i++) {
        tree[i] += val[i];
        ll parent = i + (i & (-i));
        if (parent <= n)
            tree[parent] += tree[i];
    }

    // 处理 m 个操作：真实数据 k=1 单点加、k=2 区间求和
    for (ll t = 1; t <= m; t++) {
        ll k, a, b;
        scanf("%lld %lld %lld", &k, &a, &b);
        if (k == 1) {
            update(a, b); // 在 a 处累加 b
        } else {
            // 区间和 = 两次前缀和相减
            ll ans = query_prefix(b) - query_prefix(a - 1);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
