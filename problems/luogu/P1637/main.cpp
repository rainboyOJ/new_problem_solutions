/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:09
 * update_at: 2026-08-12 22:09
 */
// P1637 三元上升子序列
// 离散化 + 两个树状数组正反两遍扫描：
// 正向统计每个位置左边比它小的个数，反向统计右边比它大的个数，
// 固定中间点 j，以 j 为中间数的三元组数 = 左小个数 * 右大个数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int n;
int a[MAXN];       // 原始输入序列
int rk[MAXN];      // rk[i]：a[i] 离散化后的排名（1..m，值越小排名越小）
int sorted_vals[MAXN]; // 排序去重后的值，用于二分求排名
int m;             // 不同值的个数（树状数组大小）

long long left_cnt[MAXN];  // left_cnt[i]：i 左边严格小于 a[i] 的个数
long long right_cnt[MAXN]; // right_cnt[i]：i 右边严格大于 a[i] 的个数

// 树状数组：单点加、前缀和，下标从 1 开始。
// 仿照 rbook 模板 fenwick（树状数组单点加与前缀和模板）。
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

    // 给位置 pos 增加 value。
    void add(int pos, T value) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tree[i] += value;
        }
    }

    // 求 [1, pos] 的前缀和。
    T prefix_sum(int pos) const {
        T answer = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            answer += tree[i];
        }
        return answer;
    }
};

// 离散化：把 a[1..n] 的值映射成 1..m 的排名，相同值排名相同。
void discretize() {
    for (int i = 1; i <= n; i++) {
        sorted_vals[i] = a[i];
    }
    sort(sorted_vals + 1, sorted_vals + n + 1);
    m = unique(sorted_vals + 1, sorted_vals + n + 1) - (sorted_vals + 1);
    for (int i = 1; i <= n; i++) {
        rk[i] = lower_bound(sorted_vals + 1, sorted_vals + m + 1, a[i]) - sorted_vals;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    discretize();

    // 正向扫描：树状数组记录已经出现过（在 i 左边）的各排名个数。
    // 严格小于 a[i] 的数，排名小于 rk[i]，个数就是前缀和 rk[i] - 1。
    Fenwick<int> bit(m);
    for (int i = 1; i <= n; i++) {
        left_cnt[i] = bit.prefix_sum(rk[i] - 1);
        bit.add(rk[i], 1);
    }

    // 反向扫描：树状数组记录 i 右边已经出现过的各排名个数。
    // 已扫描的个数 seen 减去"排名 <= rk[i] 的个数"就是严格大于 a[i] 的个数。
    Fenwick<int> bit2(m);
    int seen = 0;
    for (int i = n; i >= 1; i--) {
        right_cnt[i] = seen - bit2.prefix_sum(rk[i]);
        bit2.add(rk[i], 1);
        seen++;
    }

    // 以位置 i 为三元组中间数的方案数 = 左小个数 * 右大个数。
    // 答案最大接近 C(30000,3)，必须用 long long。
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += left_cnt[i] * right_cnt[i];
    }
    cout << ans << '\n';

    return 0;
}
