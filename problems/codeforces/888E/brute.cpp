/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 11:20
 * update_at: 2026-11-13 11:20
 */
// brute.cpp：基于位运算的 2^n 纯子集枚举基线，用于对拍验证
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m;
    }

    long long ans = 0;
    int total_states = 1 << n;

    for (int mask = 0; mask < total_states; ++mask) {
        long long cur = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                cur = (cur + a[i]) % m;
            }
        }
        ans = max(ans, cur);
    }

    cout << ans << "\n";
    return 0;
}
