/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 10:57
 * update_at: 2026-10-08 10:57
 */
// main.cpp：区间加 + 区间求和，用「差分 + 双树状数组」在 O(log n) 内完成两种操作。
//
// 记差分 d_i = a_i - a_{i-1}（a_0 = 0）。区间加 [x,y] 加 z 变成两个单点修改：
// d_x += z、d_{y+1} -= z；区间查询则要把前缀和用差分表示：
//   S_x = Σ_{i=1}^{x} a_i = Σ_{i=1}^{x} d_i·(x-i+1) = (x+1)·Σ d_i - Σ i·d_i
// 所以只要两棵树状数组分别维护 d_i 与 i·d_i，即可 O(log n) 求任意前缀和。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 题目 n <= 1e5

int n, m;
ll bit_diff[MAXN];     // 树状数组一：维护差分 d_i
ll bit_weighted[MAXN]; // 树状数组二：维护 i·d_i

// 在差分 d 的下标 idx 处加 val：两棵树同时向上更新，权值树要带上 idx 这个系数
void add_point(int idx, ll val) {
    for (int i = idx; i <= n; i += i & -i) {
        bit_diff[i] += val;
        bit_weighted[i] += val * idx;
    }
}

// 前 idx 项的和：S_idx = (idx+1)·Σd_i - Σ i·d_i（两棵树一起向下跳）
ll prefix_sum(int idx) {
    ll sum_d = 0, sum_w = 0;
    for (int i = idx; i > 0; i -= i & -i) {
        sum_d += bit_diff[i];
        sum_w += bit_weighted[i];
    }
    return (idx + 1) * sum_d - sum_w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 边读入原数组边转成差分：a_i - a_{i-1}，a_0 视为 0
    ll last = 0;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        add_point(i, a - last);
        last = a;
    }

    for (int q = 0; q < m; q++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            ll z;
            cin >> z;
            add_point(x, z);
            add_point(y + 1, -z); // y+1 超过 n 时循环条件直接跳过，相当于不加
        } else {
            cout << prefix_sum(y) - prefix_sum(x - 1) << '\n';
        }
    }

    return 0;
}
