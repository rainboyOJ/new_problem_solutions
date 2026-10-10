/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:37
 * update_at: 2026-10-08 20:37
 */
// main.cpp：打印杨辉三角形的前 n 行（2<=n<=20）。
// 用递推 a[i][j] = a[i-1][j-1] + a[i-1][j] 建表，按题面要求每行各数之间用一个空格隔开。
#include <iostream>

typedef long long ll;

// a[i][j] = 第 i 行第 j 个数 = C(i-1, j-1)。全局数组自动清零，使 a[i-1][i] 为 0，
// 于是 a[i][i] = a[i-1][i-1] + 0 = 1，每行末尾的 1 由递推自然得到。
ll a[25][25];

void solve() {
    ll n;
    if (!(std::cin >> n)) {
        return;
    }

    for (ll i = 1; i <= n; i++) {
        a[i][1] = 1; // 每行第一个数恒为 1
        for (ll j = 2; j <= i; j++) {
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
        }
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= i; j++) {
            if (j > 1) {
                std::cout << ' '; // 数之间恰一个空格，行末不留多余空格
            }
            std::cout << a[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    solve();
    return 0;
}
