/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 19:01
 */
// brute.cpp：枚举所有 m 元下标组合，取按位与的最大值。只适用于 n 很小的情况。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 25;
int n, m;
int a[maxn];
int best;

// 从下标 dep 开始决定选不选，已经选了 picked 个，当前与值为 cur
void dfs(int dep, int picked, int cur) {
    if (picked == m) {
        best = max(best, cur);
        return;
    }
    if (dep > n) return;
    if (n - dep + 1 < m - picked) return;   // 剩下的数不够选了
    // 选第 dep 个
    dfs(dep + 1, picked + 1, picked == 0 ? a[dep] : (cur & a[dep]));
    // 不选第 dep 个
    dfs(dep + 1, picked, cur);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    best = 0;
    dfs(1, 0, 0);
    cout << best << '\n';
    return 0;
}
