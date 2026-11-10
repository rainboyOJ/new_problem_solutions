/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:10
 * update_at: 2026-11-10 23:10
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    vector<string> min_s(n);
    vector<string> max_s(n);

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        string t1 = s, t2 = s;
        sort(t1.begin(), t1.end());
        sort(t2.rbegin(), t2.rend());
        min_s[i] = t1;
        max_s[i] = t2;
    }

    // 暴力 O(N^2 M) 两两比较
    string ans = "";
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (!(min_s[i] < max_s[j])) {
                ok = false;
                break;
            }
        }
        ans += (ok ? '1' : '0');
    }

    cout << ans << "\n";

    return 0;
}
