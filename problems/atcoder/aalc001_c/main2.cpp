/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-28 12:26
 * update_at: 2026-10-28 13:10
 */

// 解法一：单点赋值 + 区间和，定位靠线段树外面的二分。
//
// 不引入前缀和，也不出现区间加：线段树只维护 A 本身，支持
//   1. 单点赋值（op 1 直接把 A[i] 置为 x）
//   2. 区间和查询
// 于是不需要懒标记，代码比解法三短不少。
//
// 定位交给 rbook 的 first_true 二分模板。因为 A_i >= 0，区间和关于端点单调，
// 两个查询都能写成"在某个区间里找第一个满足 check 的位置"：
//   op 2：check(pos) 是 sum(l..pos) >= t，答案就是第一个 true 的位置；
//   op 3：check(pos) 是 sum(pos..r) < t，第一个 true 的位置减一就是答案。
// 无解不用单独判：往右的虚拟位置 n+1 恒为 true，落空就直接返回 N+1；
// 往左若第一个就 true，减一正好是 0。
// 代价是每次查询 O(log^2 n)：二分 O(log n) 步，每步一次区间和 O(log n)。

#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<long long> seg;  // 区间和

bool to_left;     // 本次定位方向：false 从 l 往右找，true 从 r 往左找
int bound;        // 固定的那个端点：往右时是 l，往左时是 r
long long need;   // 本次要凑够的和 t

void push_up(int p) { seg[p] = seg[p << 1] + seg[p << 1 | 1]; }

// 单点赋值：把 A[pos] 置为 v，沿途重算区间和
void modify(int pos, long long v, int l, int r, int p = 1) {
    if (l == r) {
        seg[p] = v;
        return;
    }
    int m = (l + r) >> 1;
    if (pos <= m) modify(pos, v, l, m, p << 1);
    else modify(pos, v, m + 1, r, p << 1 | 1);
    push_up(p);
}

// 区间和：sum(A[ql..qr])
long long query(int ql, int qr, int l, int r, int p = 1) {
    if (ql <= l && r <= qr) return seg[p];
    int m = (l + r) >> 1;
    long long s = 0;
    if (ql <= m) s += query(ql, qr, l, m, p << 1);
    if (qr > m) s += query(ql, qr, m + 1, r, p << 1 | 1);
    return s;
}

// 二分的单调谓词，两个方向共用一个函数：
//   往右：sum(l..pos) >= t 时已经凑够，返回 true；
//   往左：sum(pos..r) < t 时已经不够，返回 true。
bool check(int pos) {
    if (!to_left) {
        if (pos > n) return true;  // 虚拟可行位置：加到末尾仍不够，答案就是 N+1
        return query(bound, pos, 1, n) >= need;
    }
    if (pos > bound) return true;  // 空区间，和为 0，必然不够
    return query(pos, bound, 1, n) < need;
}

// rbook 的 first_true 模板：在 [l, r] 中查找第一个满足 check(pos) 的位置。
// 要求 check 单调：false false ... false true true ... true。
// 调用时要保证 r 是一个真实或虚拟的可行位置。
int first_true(int l, int r) {
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    seg.assign(n * 4 + 5, 0);

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        modify(i, x, 1, n);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            long long x;
            cin >> i >> x;
            modify(i, x, 1, n);
        } else if (op == 2) {
            int l;
            long long t;
            cin >> l >> t;
            to_left = false;
            bound = l;
            need = t;
            // 第一个 sum(l..pos) >= t 的位置；不存在时落在虚拟位置 n+1
            cout << first_true(l, n + 1) << '\n';
        } else {
            int r;
            long long t;
            cin >> r >> t;
            to_left = true;
            bound = r;
            need = t;
            // 第一个 sum(pos..r) < t 的位置，减一就是最后一个凑够的 l
            cout << first_true(1, r + 1) - 1 << '\n';
        }
    }

    return 0;
}
