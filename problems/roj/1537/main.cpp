/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:42
 * update_at: 2026-10-06 00:42
 */

// 每次种的树种类都不同且没有删除，所以"问区间里有多少种树"
// 等价于"问有多少条已插入的线段与询问区间相交"。
// 一条线段 [L, R] 与 [l, r] 相交 <=> L <= r 且 R >= l，
// 用容斥可以化成两个前缀计数：答案 = #{L <= r} - #{R < l}。
// 两棵树状数组分别按左端点、右端点计数即可在线维护。

#include <cstdio>

typedef long long ll;

const int MAXN = 50005;

int n, m;
ll bit_left[MAXN];  // 按左端点计数：插入 [l, r] 时下标 l+1 处 +1（下标 = 坐标+1）
ll bit_right[MAXN]; // 按右端点计数：插入 [l, r] 时下标 r+1 处 +1

// 树状数组在 x 处 +1
void add(ll bit[], int x) {
    for (; x <= n + 1; x += x & (-x))
        bit[x] += 1;
}

// 树状数组求下标 1..x 的前缀和
ll sum(ll bit[], int x) {
    ll s = 0;
    for (; x > 0; x -= x & (-x))
        s += bit[x];
    return s;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int k, l, r;
        scanf("%d %d %d", &k, &l, &r);
        if (k == 1) {
            // 种树：这个新种类是一段 [l, r]，登记到两棵计数树
            add(bit_left, l + 1);
            add(bit_right, r + 1);
        } else {
            // 与 [l, r] 相交 = 左端点 <= r 的段 - 右端点 < l 的段
            ll ans = sum(bit_left, r + 1) - sum(bit_right, l);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
