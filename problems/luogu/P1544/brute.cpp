/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:40
 * update_at: 2026-10-26 13:42
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 递归枚举两个选择序列：每层先选"下一步走左下还是右下"，到达第 n 行后
// 再枚举路径上每个点"要不要乘 3"，检查用的次数不超过 k 后统计得分。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20 + 5;

ll n, k;
ll a[MAXN][MAXN];   // 数字金字塔，a[i][j] 是第 i 行第 j 个数
ll path_[MAXN];     // 路径上每一行的列号：path_[i] 表示第 i 行走的列
int choose[MAXN];   // 选择序列：choose[i]=1 表示第 i 行路径上的点乘 3
ll best_ans;

// 完整路径已生成（path_[1..n]），统计它在选择序列 choose 下的得分。
ll calc_answer() {
    ll used = 0;
    ll sum = 0;
    for (ll i = 1; i <= n; i++) {
        ll j = path_[i];
        ll value = a[i][j];
        if (choose[i] == 1) {
            used++;
            value = value * 3;
        }
        sum += value;
    }
    if (used <= k) {
        return sum;
    }
    return LLONG_MIN; // 超过 k 次，方案不合法
}

// 枚举路径上每个点乘不乘 3，dep 是行号。生成完整 choose[1..n] 后检查。
void dfs_choose(int dep) {
    if (dep == n + 1) {
        ll value = calc_answer();
        if (value != LLONG_MIN && value > best_ans) {
            best_ans = value;
        }
        return;
    }
    // 这一层在决定第 dep 行路径上的点要不要乘 3。
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs_choose(dep + 1);
    }
}

// 枚举从顶到底的路径：当前走到第 row 行第 col 列。
void dfs_path(int row, int col) {
    path_[row] = col;
    if (row == n) {
        dfs_choose(1);
        return;
    }
    // 左下方是 (row+1, col)，右下方是 (row+1, col+1)。
    dfs_path(row + 1, col);
    dfs_path(row + 1, col + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    k = min(k, n); // 路径只有 n 个点，超过 n 的次数用不满

    best_ans = LLONG_MIN;
    dfs_path(1, 1);

    cout << best_ans << '\n';
    return 0;
}
