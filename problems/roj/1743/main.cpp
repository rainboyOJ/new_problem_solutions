/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:51
 * update_at: 2026-10-07 20:51
 */
// main.cpp：数羊。统计满足 i<j<k 且 a[i]<a[k]<a[j] 的三元组个数，即经典的 132 计数。
// 与 main.py 同一算法：只做一遍正序扫描，树状数组给出"左侧比它小的个数"，
// 再用"所有数互不相同"这一性质直接推出"右侧比它大的个数"，
// 边扫边累加 C(last,2) - pre*last。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005; // 题面上限 N <= 2e5，留几个位置作余量

int n;
int a[MAXN];    // 原始输入，题面保证互不相同（其实是 1..N 的排列）
int val[MAXN];  // 输入值的排序副本，只用于离散化
int b[MAXN];    // 离散化后的名次，取值 1..n
int bit[MAXN];  // 树状数组，下标是名次，记录"已经扫过的位置"里每个名次出现了几次

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = a[i];
    }
}

int lowbit(int x) { return x & (-x); }

// 名次 x 处计数 +1。
void add(int x) {
    for (; x <= n; x += lowbit(x)) {
        bit[x]++;
    }
}

// 已扫过的位置中，名次 <= x 的个数（前缀和）。
int query(int x) {
    int s = 0;
    for (; x > 0; x -= lowbit(x)) {
        s += bit[x];
    }
    return s;
}

void solve() {
    // 离散化：名次 rank 满足 rank-1 恰好等于"比它小的数的个数"，
    // 这一点是下面能省掉第二遍扫描的关键（合法输入下名次就是原值）。
    sort(val + 1, val + n + 1);
    for (int i = 1; i <= n; i++) {
        b[i] = int(lower_bound(val + 1, val + n + 1, a[i]) - val);
    }

    ll ans = 0;
    for (int j = 1; j <= n; j++) {
        ll pre = query(b[j] - 1); // 左侧比 a[j] 小的个数
        // 比 a[j] 小的数总共 b[j]-1 个，其中 pre 个在左侧，剩下的都在右侧；
        // 右侧元素共 n-j 个，减掉右侧比它小的，就是右侧比它大的个数 last。
        ll last = (n - j) - (b[j] - 1 - pre);
        // 以 a[j] 为最小元素、右侧任取两个更大元素共有 C(last,2) 个三元组，
        // 其中 a[j]<a[k]<a[l]（123 型）的有 pre*last 个（对每个"中间位置"计数），
        // 相减剩下的就是 a[i]<a[k]<a[j]（132 型）。
        ans += last * (last - 1) / 2 - pre * last;
        add(b[j]);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
