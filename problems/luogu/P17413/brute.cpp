/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:28
 */
// brute.cpp：小数据直接计算三种复杂度的运算次数，用来辅助验证边界。
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if ((__int128)n * n <= 500000000LL) {
        cout << "O(n^2)\n";
    } else if (n <= 500000000LL) {
        cout << "O(n)\n";
    } else {
        cout << "O(1)\n";
    }
    return 0;
}
