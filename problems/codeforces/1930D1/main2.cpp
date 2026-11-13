/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 14:49
 * update_at: 2026-11-13 14:49
 */
// main2.cpp：解法二 枚举起点 + 连续贪心跳步（O(n^2) Easy 版直观正解）
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

    // 枚举子串的左端点 l
    for (int l = 0; l < n; ++l) {
        long long cur_f = 0;
        int covered_until = -1; // 记录当前 1 已经覆盖到的最右坐标

        // 向右扩展右端点 r
        for (int r = l; r < n; ++r) {
            if (s[r] == '1' && r > covered_until) {
                // 遇到尚未被覆盖的 '1'，贪心放置在 r + 1 处，覆盖至 r + 2
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
