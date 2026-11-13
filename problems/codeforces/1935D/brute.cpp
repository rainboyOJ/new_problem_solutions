/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 11:55
 * update_at: 2026-11-13 11:55
 */
// brute.cpp：小数据 O(c^2) 双重循环暴力枚举，用于对拍验证
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void solve() {
    int n;
    long long c;
    if (!(cin >> n >> c)) return;

    unordered_set<long long> s;
    for (int i = 0; i < n; ++i) {
        long long val;
        cin >> val;
        s.insert(val);
    }

    long long valid_count = 0;
    for (long long x = 0; x <= c; ++x) {
        for (long long y = x; y <= c; ++y) {
            if (s.find(x + y) == s.end() && s.find(y - x) == s.end()) {
                valid_count++;
            }
        }
    }

    cout << valid_count << "\n";
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
