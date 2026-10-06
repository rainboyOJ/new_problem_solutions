/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:57
 * update_at: 2026-10-06 18:57
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;

// 带权并查集：kind[x] = x 到其所在集合根的异或值
const int MAXM = 20005; // M <= 10000，每个回答两个端点，至多 2M 个坐标

int fa[MAXM];          // 并查集父亲
int kind[MAXM];        // kind[x] = 前缀异或值 P[x] ^ P[fa[x]]（到父亲的异或），find 后修正为到根
int rnk[MAXM];         // 按秩合并用的树高

// 离散化后的坐标点
int xs[MAXM];          // 所有出现过的端点（l-1 与 r）
ll tot;                // 离散化后点的个数

struct Query {
    ll l, r;           // 存的是前缀坐标 l-1 与 r（原始值，未离散化）
    int parity;        // 0 = 偶数个 1，1 = 奇数个 1
};
Query qs[MAXM];        // qs[i] = 第 i 个回答（下标从 1 开始）

int m;                 // 回答数量

// 朴素 find：从 x 一路向上，同时累加异或值，再统一路径压缩
// 注意必须「先靠根的先修正」：递归返回时自根向叶累加 kind
int find_root(int x) {
    if (fa[x] == x) return x;
    int root = find_root(fa[x]);
    kind[x] ^= kind[fa[x]]; // 父亲的 kind 此时已是「父亲到根」的异或
    fa[x] = root;
    return root;
}

// 加入约束 kind[y] ^ kind[x] = parity；与已有约束矛盾返回 false
bool add_constraint(int x, int y, int parity) {
    int rx = find_root(x), ry = find_root(y);
    if (rx == ry) {
        // 同一集合：P[x] ^ P[y] 应等于 kind[x] ^ kind[y]
        return (kind[x] ^ kind[y]) == parity;
    }
    // 异根：按秩合并，把矮的挂到高的下面
    if (rnk[rx] < rnk[ry]) {
        int t = rx; rx = ry; ry = t;
        t = x; x = y; y = t;
    }
    fa[ry] = rx;
    kind[ry] = kind[x] ^ kind[y] ^ parity; // 保证 y 到 x 的路径异或恰为 parity
    if (rnk[rx] == rnk[ry]) rnk[rx]++;
    return true;
}

// 离散化：返回原始值 v 在 xs 中的下标（下标从 1 开始）
int id(ll v) {
    int low = 1, high = tot;
    while (low < high) {
        int mid = (low + high) / 2;
        if (xs[mid] < v) low = mid + 1;
        else high = mid;
    }
    return low;
}

int main() {
    ll n;
    scanf("%lld %d", &n, &m); // n 只界定前缀下标范围，判定过程与它无关
    for (int i = 1; i <= m; i++) {
        char word[10];
        scanf("%lld %lld %s", &qs[i].l, &qs[i].r, word);
        // S[l..r] 的 1 的个数奇偶 = P[l-1] ^ P[r]，前缀坐标取 l-1 与 r
        qs[i].l = qs[i].l - 1;
        qs[i].parity = (word[0] == 'o') ? 1 : 0;
    }

    // 收集所有端点做离散化（N <= 1e9，坐标不能直接开数组）
    tot = 0;
    for (int i = 1; i <= m; i++) {
        xs[++tot] = qs[i].l;
        xs[++tot] = qs[i].r;
    }
    std::sort(xs + 1, xs + tot + 1);
    tot = std::unique(xs + 1, xs + tot + 1) - (xs + 1);

    // 并查集初始化：每个离散化坐标是一个独立点
    for (int i = 1; i <= tot; i++) {
        fa[i] = i;
        kind[i] = 0;
        rnk[i] = 0;
    }

    // 按回答顺序逐条加入，第一条与前面矛盾的回答就是答案
    for (int i = 1; i <= m; i++) {
        int x = id(qs[i].l), y = id(qs[i].r);
        if (!add_constraint(x, y, qs[i].parity)) {
            printf("%d\n", i - 1); // 前 i-1 条回答可以满足，第 i 条矛盾
            return 0;
        }
    }
    printf("%d\n", m); // 所有回答都自洽
    return 0;
}
