/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
// brute.cpp：小数据暴力解，枚举每个操作是否选择，用来辅助对拍。
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int answer = n + 1;
    int all = 1 << n;
    for (int mask = 0; mask < all; mask++) {
        string t = s;
        int used = 0;
        for (int x = 1; x <= n; x++) {
            if (((mask >> (x - 1)) & 1) == 0) {
                continue;
            }
            used++;
            for (int j = x; j <= n; j += x) {
                t[j - 1] = (t[j - 1] == '0' ? '1' : '0');
            }
        }
        if (t.find('0') == string::npos) {
            answer = min(answer, used);
        }
    }
    cout << answer << '\n';
    return 0;
}
