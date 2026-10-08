/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 23:15
 * update_at: 2026-10-08 23:16
 */
// main.cpp：把 n×n 方阵两条对角线上的元素各加 10，再按 n 行输出。
#include <iostream>

typedef long long ll;

const ll MAXN = 25;   // 题面上限 n <= 20，多开几格留余量

ll n;                 // 方阵阶数，题面给定 2 <= n <= 20
ll a[MAXN][MAXN];     // 方阵，元素为小于 100 的正整数

void solve() {
    if (!(std::cin >> n)) return;                 // 无输入时安静退出
    if (n < 1 || n > MAXN) return;                // 题面保证 2 <= n <= 20，域外防御

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            std::cin >> a[i][j];
            // 主对角线 i == j，副对角线 i + j == n - 1（0-indexed）。
            // 用 or 连接天然只加一次：n 为奇数时中心格两条对角线重合，
            // 但只会在同一格上执行一次 +10（题面样例 n=5 中心 38 -> 48 可证）。
            if (i == j || i + j == n - 1) a[i][j] += 10;
        }
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            std::cout << a[i][j];
            if (j != n - 1) std::cout << ' ';     // 数之间恰一个空格，行末不留空格
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}
