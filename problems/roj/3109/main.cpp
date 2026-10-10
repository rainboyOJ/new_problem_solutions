/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 权值树状数组扫两遍，统计「V」与「∧」两种三元组个数。
#include <cstdio>

typedef long long ll;

const ll MAXN = 200005;

ll n;
ll a[MAXN];      // 原始排列（值域 1..n）
ll rev[MAXN];    // a 的反转
ll tree[MAXN];   // 权值树状数组
ll lessL[MAXN];  // lessL[j]：j 左侧比 a[j] 小的个数
ll lessR[MAXN];  // lessR[j]：j 右侧比 a[j] 小的个数

// less[j] = seq[j] 前面（已扫过的部分）比它小的元素个数
void prefix_less(ll* seq, ll* out) {
    for (ll i = 0; i <= n; i++) {
        tree[i] = 0;
    }
    for (ll j = 0; j < n; j++) {
        ll value = seq[j];
        ll i = value - 1;
        ll s = 0;
        while (i) { // 前缀和 [1, value-1]
            s += tree[i];
            i -= i & -i;
        }
        out[j] = s;
        i = value; // 把 value 插进树状数组
        while (i <= n) {
            tree[i]++;
            i += i & -i;
        }
    }
}

ll rawR[MAXN];

int main() {
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for (ll i = 0; i < n; i++) {
        rev[i] = a[n - 1 - i];
    }

    prefix_less(a, lessL);
    prefix_less(rev, rawR); // 对反转序列做同样的扫描，再翻回来
    for (ll i = 0; i < n; i++) {
        lessR[i] = rawR[n - 1 - i];
    }

    // 左侧更大的个数 = 左侧总数 j 减去左侧更小的；右侧总数是 n-1-j
    ll vCount = 0, hatCount = 0;
    for (ll j = 0; j < n; j++) {
        vCount += (j - lessL[j]) * (n - 1 - j - lessR[j]); // V：左大右大
        hatCount += lessL[j] * lessR[j];                   // ∧：左小右小
    }
    printf("%lld %lld\n", vCount, hatCount);
    return 0;
}
