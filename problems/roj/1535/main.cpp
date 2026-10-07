/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:35
 * update_at: 2026-10-06 00:35
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1000005; // 真实数据 n 最大到 1e6

int n, m;
ll bit[MAXN]; // bit[i] 存区间 (i - lowbit(i), i] 的元素和

// 返回 x 的最低位 1 代表的值
inline int lowbit(int x) {
    return x & (-x);
}

// 在位置 i 加上 v
void add(int i, ll v) {
    for (; i <= n; i += lowbit(i))
        bit[i] += v;
}

// 求前缀和 [1, i]
ll query(int i) {
    ll res = 0;
    for (; i > 0; i -= lowbit(i))
        res += bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        add(i, x); // 树状数组单点插入建树
    }

    for (int i = 1; i <= m; ++i) {
        int k, a, b;
        cin >> k >> a >> b;
        if (k == 1) {
            add(a, b); // 单点加
        } else {
            cout << query(b) - query(a - 1) << '\n'; // 区间求和
        }
    }
    return 0;
}
