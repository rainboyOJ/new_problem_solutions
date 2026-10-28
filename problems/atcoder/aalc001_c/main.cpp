#include <bits/stdc++.h>
using namespace std;

// 解法二（正式主解）：单点赋值 + 线段树上按和下降。
//
// 不转前缀和，也没有懒标记：线段树只维护 A 本身，结点存区间和。
// 定位时把"还差多少"当作余量 rem，沿树按目标方向走：
//   op 2（找最小的 r）：从左往右扫结点，整段和 < rem 就整段跳过并 rem -= 和，
//        否则往下钻，走到叶子就是答案。
//   op 3（找最大的 l）：同样，从右往左扫。
// 一次定位 O(log n)：与边界部分相交的结点 O(log n) 个，整段跳过各花 O(1)，
// 真正向下钻的只有通往答案的一条路径。
// 余量只在整段跳过时被扣掉；范围内所有下标都跳完仍不够，就是无解，返回 -1。
//
// 这版依赖 A_i >= 0：余量 rem 始终为正，"整段和 < rem"就说明段内凑不够。

int n, q;
vector<long long> seg;   // 区间和

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

// 最小的 i >= ql 使从 ql 累到 i 的和达到原 rem；无解返回 -1。
int first_reach(int ql, long long &rem, int l, int r, int p = 1) {
    if (r < ql) return -1;
    if (ql <= l && seg[p] < rem) {  // 整段都不够，整段跳过
        rem -= seg[p];
        return -1;
    }
    if (l == r) return l;  // 能走到叶子说明这一段够，叶子就是答案
    int m = (l + r) >> 1;
    int res = first_reach(ql, rem, l, m, p << 1);
    if (res != -1) return res;
    return first_reach(ql, rem, m + 1, r, p << 1 | 1);
}

// 最大的 i <= qr 使从 qr 累到 i 的和达到原 rem；无解返回 -1。
int last_reach(int qr, long long &rem, int l, int r, int p = 1) {
    if (l > qr) return -1;
    if (r <= qr && seg[p] < rem) {  // 整段都不够，整段跳过
        rem -= seg[p];
        return -1;
    }
    if (l == r) return l;
    int m = (l + r) >> 1;
    int res = last_reach(qr, rem, m + 1, r, p << 1 | 1);
    if (res != -1) return res;
    return last_reach(qr, rem, l, m, p << 1);
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
            long long rem = t;
            int r = first_reach(l, rem, 1, n);
            cout << (r == -1 ? n + 1 : r) << '\n';
        } else {
            int r;
            long long t;
            cin >> r >> t;
            long long rem = t;
            int l = last_reach(r, rem, 1, n);
            cout << (l == -1 ? 0 : l) << '\n';
        }
    }

    return 0;
}
