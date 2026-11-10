/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:11
 * update_at: 2026-11-11 00:11
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 暴力版本：针对小 k（如 k <= 3），直接枚举相乘，检测何时后 k 位重复出现
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int k;
    if (!(cin >> s >> k)) return 0;

    long long mod = 1;
    for (int i = 0; i < k; ++i) mod *= 10;

    long long n = 0;
    long long p10 = 1;
    int len = s.size();
    for (int i = 0; i < k; ++i) {
        if (len - 1 - i >= 0) {
            n += (s[len - 1 - i] - '0') * p10;
        }
        p10 *= 10;
    }
    n %= mod;

    long long cur = n;
    // 最多循环 10^k 次
    long long limit = mod * 10;
    for (long long step = 1; step <= limit; ++step) {
        cur = (1LL * cur * n) % mod;
        if (cur == n) {
            cout << step << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
