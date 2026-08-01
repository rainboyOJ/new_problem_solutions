/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 998244353LL;
    int n;
    cin >> n;
    vector<int> values(n + 1);
    for (int i = 1; i <= n; i++) cin >> values[i];

    long long answer = 0;
    for (int right = 1; right <= n; right++) {
        int current_gcd = 0;
        for (int left = right; left >= 1; left--) {
            current_gcd = gcd(current_gcd, values[left]);
            long long contribution = (long long)left * right % MOD;
            contribution = contribution * current_gcd % MOD;
            answer = (answer + contribution) % MOD;
        }
    }
    cout << answer << '\n';
    return 0;
}
