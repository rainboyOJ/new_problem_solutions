/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-11-02 09:20
 */
// brute.cpp：枚举完整的 01 选择序列，只适用于 n <= 20 的小数据。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 25;
int n, m;
int a[maxn];       // a[i]：第 i 个数；数值小于 2^30，用 int 即可
int choose[maxn];  // choose[i]：1 表示选第 i 个数，0 表示不选
int best;

// 完整选法生成后，检查选中个数，并计算这些数的按位与。
void check() {
    int cnt = 0;
    int cur = (1 << 30) - 1;  // 低 30 位全为 1，与任何输入数按位与都不改变它
    for (int i = 1; i <= n; ++i) {
        if (choose[i] == 1) {
            ++cnt;
            cur &= a[i];
        }
    }
    if (cnt == m) best = max(best, cur);
}

// 第 pos 层决定是否选第 pos 个数；到叶子时统一检查，不提前剪枝。
void dfs(int pos) {
    if (pos > n) {
        check();
        return;
    }

    choose[pos] = 0;
    dfs(pos + 1);
    choose[pos] = 1;
    dfs(pos + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    best = 0;
    dfs(1);
    cout << best << '\n';
    return 0;
}
