/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 00:00
 * update_at: 2026-08-12 22:11
 */
// main.cpp：区间开根号（下取整）+ 区间求和。
// 仿照 rbook 模板 segtree-range-assign 的 pull / update / query 结构，
// 把「区间赋值」改为「区间开根号」：维护区间最大值做剪枝，不需要懒标记。
#include <bits/stdc++.h>
using namespace std;

// 计算 x 的下取整平方根。
// double 开方可能有一点点误差，用两次乘法把结果校正到正确区间。
long long isqrt_safe(long long x) {
    long long r = (long long)sqrt((double)x);
    while ((r + 1) * (r + 1) <= x) r++;
    while (r * r > x) r--;
    return r;
}

struct SegmentTreeSqrt {
    int n = 0;
    vector<long long> sum; // sum[p] 表示节点 p 区间的和
    vector<long long> mx;  // mx[p] 表示节点 p 区间的最大值

    SegmentTreeSqrt(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        sum.assign(n * 4 + 5, 0);
        mx.assign(n * 4 + 5, 0);
    }

    // 把两个儿子的信息合并回父节点：和相加，最大值取较大者。
    void pull(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
    }

    void build(const vector<long long> &a, int l, int r, int p = 1) {
        if (l == r) {
            sum[p] = mx[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(a, l, mid, p << 1);
        build(a, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 把区间 [ql, qr] 内每个数开一次根号（下取整）。
    void sqrt_update(int ql, int qr, int l, int r, int p = 1) {
        // 剪枝：区间最大值不超过 1，说明整段都是 0 或 1，开方后不变，直接跳过。
        // 开方是单调不减的，mx[p] <= 1 就能断定整段不用改。
        if (mx[p] <= 1) return;

        if (l == r) {
            // 真正落到叶子，执行一次开方并同步最大值。
            sum[p] = isqrt_safe(sum[p]);
            mx[p] = sum[p];
            return;
        }

        int mid = (l + r) >> 1;
        if (ql <= mid) sqrt_update(ql, qr, l, mid, p << 1);
        if (qr > mid) sqrt_update(ql, qr, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 查询区间 [ql, qr] 的和。
    long long query(int ql, int qr, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) return sum[p];

        int mid = (l + r) >> 1;
        long long answer = 0;
        if (ql <= mid) answer += query(ql, qr, l, mid, p << 1);
        if (qr > mid) answer += query(ql, qr, mid + 1, r, p << 1 | 1);
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTreeSqrt seg(n);
    seg.build(a, 1, n);

    cin >> m;
    while (m--) {
        int k, l, r;
        cin >> k >> l >> r;
        // 数据中有可能 l > r，遇到这种情况需要交换。
        if (l > r) swap(l, r);
        if (k == 0)
            seg.sqrt_update(l, r, 1, n); // 区间开根号
        else
            cout << seg.query(l, r, 1, n) << '\n'; // 区间求和
    }

    return 0;
}
