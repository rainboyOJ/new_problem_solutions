/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:04
 * update_at: 2026-10-05 00:04
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 题目数据：|a| <= 10^6 且题面保证 |a^n| <= 10^6，int 完全够用。
int a, n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> n;

    // 朴素累乘：循环 n 次把 result *= a，n<=10^4，O(n) 完全可过。
    ll result = 1;
    for (int i = 0; i < n; i++) {
        result *= a;
    }

    cout << result << endl;

    return 0;
}