/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:32
 * update_at: 2026-07-11 12:33
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

long long round_to(long long x, long long base) {
    long long rem = x % base;
    if (rem < base / 2) {
        return x - rem;
    }
    return x + base - rem;
}

long long chain_round(long long x, long long target) {
    for (long long base = 10; base <= target; base *= 10) {
        x = round_to(x, base);
    }
    return x;
}

bool is_different(long long x) {
    long long target = 1;
    while (target < x) {
        target *= 10;
    }
    return chain_round(x, target) != round_to(x, target);
}

long long solve_one(long long n) {
    long long ans = 0;
    for (long long x = 2; x <= n; x++) {
        if (is_different(x)) {
            ans++;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << solve_one(n) << '\n';
    }

    return 0;
}
