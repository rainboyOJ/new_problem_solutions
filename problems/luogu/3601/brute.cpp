/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据朴素解，按定义枚举 1..x 并检查最大公约数。

const int MOD = 666623333;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long left, right;
    cin >> left >> right;

    long long answer = 0;
    for (long long value = left; value <= right; value++) {
        for (long long other = 1; other <= value; other++) {
            if (gcd(value, other) != 1) answer++;
        }
        answer %= MOD;
    }

    cout << answer << '\n';
    return 0;
}
