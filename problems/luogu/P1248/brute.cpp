/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:50
 * update_at: 2026-11-09 20:53
 */
// brute.cpp：小数据暴力解，枚举作业的全排列，模拟两台机器流水，取总时间最小的顺序。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 12;
ll a[maxn], b[maxn]; // a[i]、b[i]：作业 i 在 A、B 车间的加工时间
int perm[maxn];      // 当前排列
bool used[maxn];     // used[i]：作业 i 是否已经在当前排列中
ll best_time;        // 当前最优总时间
int best_perm[maxn]; // 最优排列

// 按给定排列顺序模拟两台机器，返回总加工时间。
ll simulate(int n) {
    ll finish_a = 0;
    ll finish_b = 0;
    for (int i = 1; i <= n; ++i) {
        int id = perm[i];
        finish_a += a[id];
        finish_b = max(finish_b, finish_a) + b[id];
    }
    return finish_b;
}

// 深度优先枚举全排列：dep 表示正在确定排列的第 dep 个位置。
void dfs_perm(int dep, int n) {
    if (dep > n) {
        ll t = simulate(n);
        if (t < best_time) {
            best_time = t;
            for (int i = 1; i <= n; ++i) best_perm[i] = perm[i];
        }
        return;
    }
    for (int id = 1; id <= n; ++id) {
        if (used[id]) continue;
        used[id] = true;
        perm[dep] = id;
        dfs_perm(dep + 1, n);
        used[id] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    best_time = LLONG_MAX;
    dfs_perm(1, n);

    cout << best_time << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << best_perm[i];
    }
    cout << '\n';

    return 0;
}
