/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:26
 * update_at: 2026-11-10 23:26
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 暴力验证：枚举所有 (A, B, i, C)
int calc_odd(const string& s, int l, int r) {
    int cnt[26] = {0};
    for (int i = l; i <= r; ++i) {
        cnt[s[i] - 'a']++;
    }
    int res = 0;
    for (int i = 0; i < 26; ++i) {
        if (cnt[i] % 2 != 0) res++;
    }
    return res;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    long long ans = 0;

    // 枚举 AB 的长度
    for (int len = 2; len < n; ++len) {
        string ab = s.substr(0, len);

        // 枚举 A 的长度
        for (int a_len = 1; a_len < len; ++a_len) {
            int f_a = calc_odd(s, 0, a_len - 1);

            // 枚举重复次数 i
            for (int i = 1; i * len < n; ++i) {
                // 检查前 i * len 是否全是 ab 重复
                bool ok = true;
                for (int k = 0; k < len; ++k) {
                    if (s[(i - 1) * len + k] != ab[k]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) break;

                int f_c = calc_odd(s, i * len, n - 1);
                if (f_a <= f_c) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
