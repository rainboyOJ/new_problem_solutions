/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:29
 */
// brute.cpp：直接按递推式逐项计算，只用于小下标对拍。
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    long long left, right;
    cin >> m >> left >> right;
    vector<int> coefficient(m + 1);
    for (int i = 1; i <= m; i++) cin >> coefficient[i];

    vector<int> sequence(right + 1, 0);
    sequence[0] = 1;
    for (int i = 1; i <= right; i++) {
        long long value = 0;
        for (int j = 1; j <= m && j <= i; j++) {
            value += coefficient[j] * 1LL * sequence[i - j] % MOD;
            if (value >= MOD) value -= MOD;
        }
        sequence[i] = (int)value;
    }
    for (long long i = left; i <= right; i++) cout << sequence[i] << '\n';

    return 0;
}
