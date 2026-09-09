/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:08
 * update_at: 2026-08-28 19:08
 */
// brute.cpp：小数据暴力解，直接按题意逐步"把当前数舍入到 10^j 的倍数"。
// 用 long long 整数模拟：舍去低位 = 除以 10^j 再乘回；第 j 位 >= 5 就再 +10^j。
// 连锁进位由整数加法自动完成，是最贴近题意的写法。
// 只适合 k <= 15 左右的小数据（对拍用），k 大时数装不进 long long。
#include <bits/stdc++.h>
using namespace std;

int k;
string s;

// 计算 10^e
long long pow10(int e) {
    long long res = 1;
    for (int i = 0; i < e; i++) res *= 10;
    return res;
}

void solve() {
    cin >> k >> s;

    // 字符串转成整数（小数据才装得下）
    long long n = 0;
    for (int i = 0; i < k; i++) n = n * 10 + (s[i] - '0');

    cout << n;
    for (int j = 1; j <= k - 1; j++) { // 第 j 步处理从右数第 j 位
        long long p = pow10(j);                    // 10^j
        long long digit = (n / (p / 10)) % 10;     // 当前数从右数第 j 位的数字
        if (digit >= 5)
            n = (n / p + 1) * p; // 舍去低位并向前进 1（进位自动连锁）
        else
            n = (n / p) * p;     // 只舍去低位
        cout << " -> " << n;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}