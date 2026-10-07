/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 18:53
 * update_at: 2026-10-07 18:53
 *
 * 一本通 1726《矩阵》（同 BZOJ 4500）
 *
 * 建模：矩阵初值全 0，对第 i 行整体加减的总净次数记 r_i，对第 j 列记 c_j
 * （加减可互相抵消，所以 r_i、c_j 是任意整数，操作序列存在 <=> 存在整数 r、c）。
 * 于是限制 (x, y, c) 就是 r_x + c_y = c，全是"等式约束"，可行性 = 方程组是否有整数解。
 *
 * 做法（带权并查集）：把每一行、每一列都看成一个点，行点编号 1..n，列点编号 n+1..n+m，
 * 并令列点 n+y 的"值"取 -(第 y 列的净操作数)，则每条限制化为**差值等式**
 *      值(x) - 值(n+y) = c,
 * 这正是带权并查集能维护的形式：同集合内核对值差，不同集合则按值差合并。
 *
 * 正确性：约束全为整系数等式，解在有理数域存在时并查集给出的偏移量全为整数，
 * 故整数可解性与实数可解性一致；矛盾判据"环上值差之和 != 0"等价于无解。
 *
 * 数据范围（content.md）：T <= 5；1 <= n,m,k <= 1000 且 k <= n*m；c 的区间题面未给，用 ll 承载。
 * 复杂度：每组 O((n+m) + k*alpha)，T <= 5、n+m <= 2000、k <= 1000，远低于 2000 ms。
 */

#include <cstdio>

typedef long long ll;

const int MAXV = 2005; // 行点 1..n 与列点 n+1..n+m，n+m <= 2000

ll fa[MAXV];  // fa[i] 是并查集父节点，fa[i] == i 表示 i 是根
ll val[MAXV]; // val[i] = 值(i) - 值(fa[i])，即 i 到父节点的值差

// 找 x 的根，同时把路径上每点的 val 压成"值(点) - 值(根)"
ll find_root(ll x) {
    ll root = x;
    while (fa[root] != root) root = fa[root];

    // 第一遍：求出 total = 值(x) - 值(root)
    ll total = 0;
    ll node;
    for (node = x; node != root; node = fa[node]) total += val[node];

    // 第二遍：自 x 向根压路径，pre = 值(x) - 值(node)
    ll pre = 0;
    node = x;
    while (node != root) {
        ll nxt = fa[node];
        ll old = val[node];
        val[node] = total - pre; // 值(node) - 值(root)
        fa[node] = root;         // 路径压缩
        pre += old;
        node = nxt;
    }
    return root;
}

int main() {
    ll T;
    scanf("%lld", &T);
    while (T--) {
        ll n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);

        for (ll i = 1; i <= n + m; i++) {
            fa[i] = i;
            val[i] = 0;
        }

        bool ok = true; // 是否存在满足全部限制的整数操作序列
        for (ll i = 1; i <= k; i++) {
            ll x, y, c;
            scanf("%lld %lld %lld", &x, &y, &c);

            ll col = n + y; // 第 y 列对应的列点编号
            ll root_x = find_root(x);
            ll root_col = find_root(col);

            if (root_x == root_col) {
                // 同一集合：值(x) - 值(col) 已被推出，必须恰好等于 c
                if (val[x] - val[col] != c) ok = false;
            } else {
                // 不同集合：把 col 的根挂到 x 的根下，新根到新父的值差由等式反解
                fa[root_col] = root_x;
                val[root_col] = val[x] - val[col] - c;
            }
        }
        printf("%s\n", ok ? "Yes" : "No");
    }
    return 0;
}
