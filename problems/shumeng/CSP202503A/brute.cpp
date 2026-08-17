/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:46
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b, c, l, r;
    cin >> b >> c >> l >> r;

    // 朴素做法：逐个检查 [l,r] 中的每个整数，只累加偶数的函数值
    long long answer = 0;
    for (long long x = l; x <= r; x++) {
        if (x % 2 == 0) answer += x * x + b * x + c;
    }
    // 采样间距仍为 2，函数值之和乘以 2 得到估算积分
    cout << answer * 2 << '\n';
    return 0;
}
