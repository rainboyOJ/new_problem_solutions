/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:20
 * update_at: 2026-11-13 09:20
 */
// brute.cpp：基于 0-1 状态子集枚举的基线解法，用于小数据对拍验证
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    long long m;
    if (!(cin >> n >> m)) return;

    vector<long long> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    long long min_cost = 1e18;

    // 枚举 2^n 种选择子集
    int total_states = 1 << n;
    for (int mask = 0; mask < total_states; ++mask) {
        long long cur_space = 0;
        long long cur_cost = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                cur_space += a[i];
                cur_cost += b[i];
            }
        }
        if (cur_space >= m) {
            min_cost = min(min_cost, cur_cost);
        }
    }

    if (min_cost >= 1e18) {
        cout << -1 << "\n";
    } else {
        cout << min_cost << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
