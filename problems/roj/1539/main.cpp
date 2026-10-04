/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:02
 * update_at: 2026-10-05 07:02
 */

// CQOI 2006 简单题：区间 0/1 翻转 + 单点询问。
// 用异或差分 d[i] = a[i] ^ a[i-1]：翻转 [L,R] 只改 d[L] 和 d[R+1]，
// 单点 a[i] 就是 d[1..i] 的异或前缀和。
// 指令在线交错给出，故用异或树状数组维护 d，两种操作都是 O(log n)。

#include <cstdio>

typedef long long ll;

const int MAXN = 1e5 + 5;

int n, m;
ll tree[MAXN]; // 异或树状数组：tree[i] 维护差分区间 (i - lowbit(i), i] 的异或和

// 取 x 最低位的 1：树状数组每个结点管辖的长度
int lowbit(int x) {
    return x & -x;
}

// 单点取反 d[i]，并向上更新所有管辖到 i 的结点
void flip(int i) {
    for (; i <= n; i += lowbit(i))
        tree[i] ^= 1;
}

// 返回 d[1] ^ d[2] ^ ... ^ d[i]，即原数组 a[i] 的当前值
ll prefix_xor(int i) {
    ll res = 0;
    for (; i > 0; i -= lowbit(i))
        res ^= tree[i];
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int t = 1; t <= m; ++t) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int left, right;
            scanf("%d %d", &left, &right);
            flip(left); // 翻转区间左端：开启一段翻转
            if (right < n)
                flip(right + 1); // 右端之后撤销翻转；R = n 时 d[n+1] 越界且永不被查询读到，跳过
        }
        else {
            int idx;
            scanf("%d", &idx);
            printf("%lld\n", prefix_xor(idx));
        }
    }
    return 0;
}
