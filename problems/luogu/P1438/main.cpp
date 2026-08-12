/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:03
 * update_at: 2026-08-12 22:03
 */
#include <bits/stdc++.h>
using namespace std;

// 仿照 rbook 模板 fenwick：单点加、前缀和，下标从 1 开始。
template <typename T>
struct Fenwick {
    int n = 0;
    vector<T> tree;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    static int lowbit(int x) {
        return x & -x;
    }

    // 给差分数组的一个位置增加 value。
    void add(int pos, T value) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tree[i] += value;
        }
    }

    // 求差分数组 [1, pos] 的前缀和。
    T prefix_sum(int pos) const {
        T answer = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            answer += tree[i];
        }
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Fenwick<long long> c_diff(n); // 常数系数 (K - l*D) 的差分数组
    Fenwick<long long> x_diff(n); // 下标系数 D 的差分数组

    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            long long K, D;
            cin >> l >> r >> K >> D;
            // 第 i 项增加 (K - l*D) + i*D，两个系数都在 [l,r] 上加常数，
            // 于是差分数组只需在 l 处加、r+1 处减。
            long long c = K - l * D;
            c_diff.add(l, c);
            c_diff.add(r + 1, -c);
            x_diff.add(l, D);
            x_diff.add(r + 1, -D);
        } else {
            int p;
            cin >> p;
            // a[p] = 初始值 + 常数系数前缀和 + p * 下标系数前缀和。
            long long ans = a[p] + c_diff.prefix_sum(p) + p * x_diff.prefix_sum(p);
            cout << ans << '\n';
        }
    }

    return 0;
}
