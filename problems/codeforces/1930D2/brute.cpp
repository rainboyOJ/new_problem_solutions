/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 15:05
 * update_at: 2026-11-13 15:05
 */
// brute.cpp：基于 O(n^2) 连续区间贪心跳步的对照解法，用于对拍验证
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;
    string s;
    cin >> s;

    long long total_ans = 0;
    for (int l = 0; l < n; ++l) {
        long long cur_f = 0;
        int covered_until = -1;
        for (int r = l; r < n; ++r) {
            if (s[r] == '1' && r > covered_until) {
                cur_f++;
                covered_until = r + 2;
            }
            total_ans += cur_f;
        }
    }
    cout << total_ans << "\n";
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
