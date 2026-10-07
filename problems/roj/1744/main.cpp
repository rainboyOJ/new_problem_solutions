/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:59
 * update_at: 2026-10-07 21:59
 */
// 一本通 1744《跳台阶》
// 把 N 个台阶分给两条链，每条链从地面(高度 0)出发，按台阶编号递增行走，
// 一条链的体力 = |首台阶高 - 0| + Σ|相邻两台阶高之差|（题面给出的求和式缺了绝对值，
// 由样例 [1,3,1] 答案为 4 可确认是绝对差之和，否则求和式会望远镜式相消变成 H_last）。
// 记 f_i(x) = 处理完前 i 个台阶、第 i 个台阶是某条链的末尾、另一条链末尾高度为 x 的最小总体力。
//   1) 第 i+1 个台阶接在 i 后面：f_{i+1}(x) = f_i(x) + |H_{i+1} - H_i|（整体懒加 c）
//   2) 第 i+1 个台阶换到另一条链：两条链末尾互换，f_{i+1}(H_i) = min_x f_i(x) + |H_{i+1} - x|
// 第二条即锥形下包络 φ(h) = min_x f_i(x) + |h - x|
//          = min( h + min_{x<=h}(f(x)-x),  -h + min_{x>h}(f(x)+x) )，
// 用两棵树状数组（前缀最小 / 反转下标后的前缀最小）维护 f(x)-x 与 f(x)+x 即可 O(log n) 求值，
// 单点下调键 H_i，全局懒加记录公共增量。答案 = min_x f_n(x)，全程维护该最小值 m。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;      // 台阶数上限
const ll INF = 1LL << 62;     // 无穷大：真实答案不超过 5e14，远小于它

int n;                        // 台阶数
ll h[MAXN];                   // h[0..n-1] 即题面第 1..n 个台阶的高度
ll xs[MAXN];                  // 值域压缩后的候选"另一条链的末尾高度"：地面 0 加上所有台阶高度
int R;                        // 压缩后点数
ll treeA[MAXN];               // 树状数组：前缀 min (f(x) - x)
ll treeB[MAXN];               // 树状数组：反转下标上的前缀 min，用来查 x > h 的 min (f(x) + x)
ll add;                       // 全局懒加：所有状态共同增加的量（树状数组里存的是减去 add 的值）

// 把 0 下标位置 pos 的值下调为 val（树状数组只能"变小"，正好够用）
void upd_min(ll tree[], int pos, ll val) {
    for (int i = pos + 1; i <= R; i += i & -i) {
        if (val < tree[i]) tree[i] = val;
    }
}

// 询问 0..pos 的最小值；pos < 0 表示区间为空，返回 INF
ll qry_min(ll tree[], int pos) {
    ll res = INF;
    for (int i = pos + 1; i > 0; i -= i & -i) {
        if (tree[i] < res) res = tree[i];
    }
    return res;
}

// 值 x 在压缩值域中的下标
int rk(ll x) {
    return (int)(lower_bound(xs, xs + R, x) - xs);
}

int main() {
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%lld", &h[i]);

    int tot = 0;
    xs[tot++] = 0;                                    // 空链的末尾就是地面
    for (int i = 0; i < n; i++) xs[tot++] = h[i];
    sort(xs, xs + tot);
    R = (int)(unique(xs, xs + tot) - xs);

    for (int i = 1; i <= R; i++) {                    // 树状数组 1 号下标起用
        treeA[i] = INF;
        treeB[i] = INF;
    }

    // 初始状态 f_1：第 1 个台阶自成一链，另一条链停在地面，体力 = H_1
    ll m = h[0];
    int p0 = rk(0);
    upd_min(treeA, p0, h[0]);
    upd_min(treeB, R - 1 - p0, h[0]);

    for (int i = 1; i < n; i++) {
        ll c = llabs(h[i] - h[i - 1]);                // 接在同一条链后面的增量
        ll cur = h[i];
        int pos = rk(cur);

        // 换链：φ(cur) = min( cur + min_{x<=cur}(f(x)-x),  -cur + min_{x>cur}(f(x)+x) )
        ll t = cur + qry_min(treeA, pos) + add;
        ll other = -cur + qry_min(treeB, R - 2 - pos) + add;   // x > cur 的部分（反转下标）
        if (other < t) t = other;

        m = min(m + c, t);                            // m 即 min_x f(x)
        add += c;
        // 键 H_{i-1} 的新值恰为 t（t <= f(H_{i-1}) + c 恒成立），单点下调即可
        int k = rk(h[i - 1]);
        ll base = t - add;
        upd_min(treeA, k, base - xs[k]);
        upd_min(treeB, R - 1 - k, base + xs[k]);
    }

    printf("%lld\n", m);
    return 0;
}
