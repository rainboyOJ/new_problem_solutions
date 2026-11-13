/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 13:00
 * update_at: 2026-11-13 13:00
 */
// brute.cpp：基于所有子串暴力提取 + 贪心跳步的对照解法
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 单个子串的贪心覆盖求解：O(len)
long long calc_f(const string& s, int l, int r) {
    long long ans = 0;
    int idx = l;
    while (idx <= r) {
        if (s[idx] == '1') {
            ans++;
            idx += 3; // 贪心放置在 idx+1 处，覆盖 idx, idx+1, idx+2，直接跳到 idx+3
        } else {
            idx++;
        }
    }
    return ans;
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    string s;
    cin >> s;

    long long total_sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            total_sum += calc_f(s, i, j);
        }
    }

    cout << total_sum << "\n";
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
