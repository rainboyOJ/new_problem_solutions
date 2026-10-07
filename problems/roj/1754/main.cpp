/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:30
 * update_at: 2026-10-07 21:35
 */
// 一本通 1754《栈的维护》
//
// 把一段连续操作看成一个函数 F(x) = max(need, x + cap)：
//   x 是从这段右侧灌进来的"弹出需求"个数，F(x) 是最终还要继续向左侧弹出的个数。
// 单个叶子：压入 v -> F(x) = max(0, x - 1)；弹出 v -> F(x) = x + v。
// 两个函数复合仍是这个形状：F_{L+R}(x) = F_L(F_R(x)) = max(max(needL, needR + capL), x + capL + capR)。
// 因此每个结点存 cap（= 弹出值之和 - 压入次数）、need（= F(0)）就够了。
// 再加上 sum = "右侧没有需求时本段留在栈中的元素之和"，根结点的 sum 就是答案。
// 需求会从右往左吃掉压入的元素，所以 sum 不能由儿子的 sum 直接相加，
// 需要一次 O(log m) 的单链下推（retain）；单点修改要重算 O(log m) 个结点，总复杂度 O(log^2 m)。
// 元素和的上界约 2e5*1e4 = 2e9，cap/need/sum 全部用 long long。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 200000 + 5;

struct Op {
    ll k;  // 0 压入，1 弹出
    ll v;  // k=0 时为入栈的数，k=1 时为弹出个数
};

struct Node {
    ll cap;  // 本段 cap 之和：弹出值之和减去压入次数，可以为负
    ll need; // 本段在右侧没有外部需求时仍需向左侧弹出的个数，恒 >= cap
    ll sum;  // 右侧没有外部需求时，本段最终留在栈中的元素之和
};

int m, q;
int base;      // 线段树叶子数，取 2 的幂，右端空位用恒等段（F(x) = x）填充
int leafOf;    // 第 1 个操作对应的叶子下标
Op op[MAXN];
Node seg[MAXN * 4];  // 2*base 最大 524288 < MAXN*4

// 本段在右侧灌进 y 个需求时，最终留在栈中的元素之和。
// 只能沿单条链下推：需求先吃掉右下方的压入，最多走 O(log m) 步。
ll retain(int k, ll y) {
    ll kept = 0;
    while (true) {
        if (y <= 0) return kept + seg[k].sum;             // 没有需求，整段保留
        if (y >= seg[k].need - seg[k].cap) return kept;   // 需求吃光本段全部存活元素
        int ls = k << 1, rs = ls | 1;
        ll roomR = seg[rs].need - seg[rs].cap;            // 右儿子能吸收的需求上限
        if (y <= roomR) {
            // 右儿子独自吸收：左儿子收到的需求恒为 needR，故左儿子贡献固定
            kept += seg[k].sum - seg[rs].sum;
            k = rs;
        } else {
            // 右儿子被吃光，剩下的需求 y + capR 灌进左儿子
            y += seg[rs].cap;
            k = ls;
        }
    }
}

// 用左右儿子重算 k。sum 不能直接相加：右儿子的 needR 会向左侧（即左儿子）要元素
void pull(int k) {
    int ls = k << 1, rs = ls | 1;
    seg[k].cap = seg[ls].cap + seg[rs].cap;
    seg[k].need = max(seg[ls].need, seg[rs].need + seg[ls].cap);
    seg[k].sum = seg[rs].sum + retain(ls, seg[rs].need);
}

// 叶子：压入 v 是"供给 1 个元素"，弹出 v 是"纯需求 v"
void set_leaf(int k, ll kk, ll vv) {
    if (kk == 1) {
        seg[k].cap = vv;
        seg[k].need = vv;
        seg[k].sum = 0;
    } else {
        seg[k].cap = -1;
        seg[k].need = 0;
        seg[k].sum = vv;
    }
}

int main() {
    if (scanf("%d %d", &m, &q) != 2) return 0;
    base = 1;
    while (base < m) base <<= 1;
    leafOf = base;  // 第 1 个操作用下标 1，落在 base + 1 - 1 = base 这个叶子上
    for (int i = 1; i <= m; ++i) scanf("%lld %lld", &op[i].k, &op[i].v);
    for (int i = 1; i <= 2 * base; ++i) {  // 空位是恒等段，不影响结果
        seg[i].cap = 0;
        seg[i].need = 0;
        seg[i].sum = 0;
    }
    for (int i = 1; i <= m; ++i) set_leaf(leafOf + i - 1, op[i].k, op[i].v);
    for (int k = base - 1; k >= 1; --k) pull(k);
    for (int i = 1; i <= q; ++i) {
        int c;
        ll kk, vv;
        scanf("%d %lld %lld", &c, &kk, &vv);
        op[c].k = kk;
        op[c].v = vv;
        set_leaf(leafOf + c - 1, kk, vv);
        for (int k = (leafOf + c - 1) >> 1; k >= 1; k >>= 1) pull(k);
        printf("%lld\n", seg[1].sum);  // 根在"右侧无需求"下保留的和就是答案
    }
    return 0;
}
