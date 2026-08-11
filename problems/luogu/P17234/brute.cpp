/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 18:01
 */
// brute.cpp：小数据暴力解，直接枚举所有区间并计算 mex 与补区间最小值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;       // 暴力解复杂度为 O(n^3)，只适合小数据验证
const int INF = 1000000000; // 补区间为空时，cmin 保持这个很大的值

int n;
int a[MAXN];    // 输入数列，下标从 1 开始
int used[MAXN]; // used[x] = 1 表示当前区间内出现过值 x，用于求 mex

// 计算区间 [l, r] 的 mex：最小的没有在区间内出现过的非负整数。
int calc_mex(int l, int r) {
    // 清空标记数组，准备统计区间 [l, r] 内出现了哪些数
    for (int i = 0; i <= n + 1; i++) used[i] = 0;
    for (int i = l; i <= r; i++) {
        // 值太大时不可能成为 mex，不需要标记
        if (a[i] <= n + 1) used[a[i]] = 1;
    }

    // 从小到大找第一个没有出现过的数
    int mex_value = 0;
    while (used[mex_value]) mex_value++;
    return mex_value;
}

// 计算区间 [l, r] 的补区间最小值：由左边 [1, l-1] 和右边 [r+1, n] 两部分拼成。
int calc_cmin(int l, int r) {
    int cmin = INF;
    for (int i = 1; i < l; i++) cmin = min(cmin, a[i]);
    for (int i = r + 1; i <= n; i++) cmin = min(cmin, a[i]);
    return cmin;
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() {
    long long ans = 0;
    // 枚举所有子区间的左右端点 [l, r]
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            // 满足 mex == cmin 的区间计入答案
            if (calc_mex(l, r) == calc_cmin(l, r)) ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
