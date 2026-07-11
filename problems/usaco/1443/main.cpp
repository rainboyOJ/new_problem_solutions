/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:32
 * update_at: 2026-07-11 12:33
 */
#include <bits/stdc++.h>
using namespace std;

long long solve_one(long long n) {
    long long ans = 0;
    long long lower = 0; // 当前位数下的 444...4，这个端点本身不算
    long long pow10 = 1;

    for (int len = 1; len <= 10; len++) {
        lower = lower * 10 + 4;
        long long upper = 5 * pow10 - 1; // 当前位数下的 499...9
        long long high = min(n, upper);
        if (high > lower) {
            ans += high - lower;
        }
        pow10 *= 10;
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
