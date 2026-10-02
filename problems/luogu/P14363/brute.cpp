/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:52
 * update_at: 2026-10-01 22:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举每条规则和每个起点，检查替换后是否等于目标串，只适合很小的数据。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int n, q;
string left_part[MAXN];  // 规则 i 的替换前串 s1
string right_part[MAXN]; // 规则 i 的替换后串 s2

// 检查把 a 的 [start, start+len) 子串用规则 id 替换后是否恰好等于 b
bool can_replace_at(const string &a, const string &b, int id, int start) {
    int len = left_part[id].size();
    int alen = a.size();
    if (start + len > alen) {
        return false;
    }

    // 被替换区间必须与规则的替换前串完全相同
    for (int i = 0; i < len; i++) {
        if (a[start + i] != left_part[id][i]) {
            return false;
        }
    }

    // 替换区间外保持原样，区间内换成替换后串，逐位和 b 比较
    for (int i = 0; i < alen; i++) {
        char after_char = a[i];
        if (start <= i && i < start + len) {
            after_char = right_part[id][i - start];
        }
        if (after_char != b[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> left_part[i] >> right_part[i];
    }

    while (q--) {
        string a, b;
        cin >> a >> b;

        ll ans = 0;
        if (a.size() == b.size()) {
            int alen = a.size();
            for (int id = 1; id <= n; id++) {
                int plen = left_part[id].size();
                for (int start = 0; start + plen <= alen; start++) {
                    if (can_replace_at(a, b, id, start)) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
