/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 排队：树状数组上倍增求「剩余身高中第 k 小」。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll MAXN = 100005;

ll n;
ll a[MAXN];    // a[i]：第 i 头牛前面比它矮的数量（i ≥ 2）
ll tree[MAXN]; // 树状数组中 tree[i] 记录 (i-lowbit(i), i] 里空闲身高的个数
ll ans[MAXN];

// 树状数组上倍增：返回剩余（未被占用）身高中第 k 小的下标（1-based）
ll kth_free(ll k, ll log) {
    ll pos = 0;
    for (ll p = log; p >= 0; p--) {
        ll step = 1LL << p;
        ll nxt = pos + step;
        if (nxt <= n && tree[nxt] < k) { // 前缀和不够 k，第 k 小还在更右边
            pos = nxt;
            k -= tree[nxt];
        }
    }
    return pos + 1;
}

int main() {
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    a[1] = 0; // 第 1 头牛前面没有牛
    for (ll i = 2; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for (ll i = 1; i <= n; i++) {
        tree[i] = i & -i; // 初值即建树：所有身高都空闲
    }

    ll log = 1;
    while ((1LL << log) <= n) {
        log++;
    }
    log--; // 2^log ≤ n < 2^(log+1)

    for (ll i = n; i >= 1; i--) {
        // 从后往前确定：第 i 头牛的身高是剩余身高里第 a[i]+1 小的
        ll h = kth_free(a[i] + 1, log);
        ans[i] = h;
        ll p = h;
        while (p <= n) { // 身高 h 已被占用
            tree[p] -= 1;
            p += p & -p;
        }
    }

    for (ll i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
