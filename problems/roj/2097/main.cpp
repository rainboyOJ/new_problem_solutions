/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:27
 * update_at: 2026-10-06 13:27
 */

// 【模板】线段树乘法：区间乘 + 区间求和，乘法懒标记线段树。

#include <cstdio>

typedef long long ll;

const int MAXN = 100005; // n <= 1e5，线段树开 4n

ll MOD;             // 模数 p，读入后覆盖，树里所有取模都用它
ll tree[MAXN << 2]; // tree[i]：节点 i 负责区间的元素和（已取模）
ll tag[MAXN << 2];  // tag[i]：区间每个数还欠着的乘法，初始 1 表示不欠账
ll a[MAXN];         // 初始序列，1-based

// 把乘法 v 记到节点 i：区间和乘 v，欠账也乘 v（两次乘法复合成相乘）
void apply_mul(int i, ll v) {
    tree[i] = tree[i] * v % MOD;
    tag[i] = tag[i] * v % MOD;
}

// 用左右孩子的和重建节点 i 的区间和
void push_up(int i) {
    tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
}

// 要进孩子前把节点 i 攒下的乘法标记结算给两个孩子，然后清回 1
void push_down(int i) {
    if (tag[i] != 1) {
        apply_mul(i << 1, tag[i]);
        apply_mul(i << 1 | 1, tag[i]);
        tag[i] = 1;
    }
}

// 建树：叶子取 a[l]，内部节点由孩子加出来
void build(int i, int l, int r) {
    tag[i] = 1; // 乘法恒等元，表示不欠账
    if (l == r) {
        tree[i] = a[l] % MOD;
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    push_up(i);
}

// 节点 i 负责 [l, r]，把目标区间 [L, R] 内每个数乘上 v
void range_mul(int i, int l, int r, int L, int R, ll v) {
    if (L <= l && r <= R) { // 整段覆盖：和与欠账同步乘，不进孩子
        apply_mul(i, v);
        return;
    }
    push_down(i); // 要下钻，先结清攒下的标记
    int mid = (l + r) >> 1;
    if (L <= mid)
        range_mul(i << 1, l, mid, L, R, v);
    if (R > mid)
        range_mul(i << 1 | 1, mid + 1, r, L, R, v);
    push_up(i);
}

// 节点 i 负责 [l, r]，返回目标区间 [L, R] 内元素和（模 MOD）
ll range_sum(int i, int l, int r, int L, int R) {
    if (L <= l && r <= R)
        return tree[i];
    push_down(i); // 孩子里可能压着没结算的乘法
    int mid = (l + r) >> 1;
    ll s = 0;
    if (L <= mid)
        s = range_sum(i << 1, l, mid, L, R);
    if (R > mid)
        s += range_sum(i << 1 | 1, mid + 1, r, L, R);
    return s % MOD;
}

int main() {
    int n, m;
    scanf("%d %d %lld", &n, &m, &MOD);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);

    for (int t = 1; t <= m; t++) {
        int op;
        scanf("%d", &op);
        if (op == 1) { // 1 x y k：区间 [x, y] 每个数乘 k
            int x, y;
            ll k;
            scanf("%d %d %lld", &x, &y, &k);
            range_mul(1, 1, n, x, y, k % MOD); // k 先取模，标记不会越滚越大
        } else { // 2 x y：输出区间 [x, y] 的和模 p
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%lld\n", range_sum(1, 1, n, x, y));
        }
    }
    return 0;
}
