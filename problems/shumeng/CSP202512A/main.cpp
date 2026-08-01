/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> value(n + 1);
    for (int i = 1; i <= n; i++) cin >> value[i];
    vector<vector<int>> s(m);
    vector<int> sx(m, 0);
    for (int i = 0; i < m; i++) {
        int len;
        cin >> len;
        s[i].resize(len);
        for (int j = 0; j < len; j++) {
            cin >> s[i][j];
            sx[i] ^= value[s[i][j]];
        }
    }
    vector<vector<int>> t(m);
    vector<int> tx(m, 0);
    for (int i = 0; i < m; i++) {
        int len;
        cin >> len;
        t[i].resize(len);
        for (int j = 0; j < len; j++) {
            cin >> t[i][j];
            tx[i] ^= value[t[i][j]];
        }
    }
    for (int i = 0; i < m; i++) {
        bool same_set = s[i] == t[i];
        bool same_xor = sx[i] == tx[i];
        cout << (same_set == same_xor ? "correct" : "wrong") << '\n';
    }
    return 0;
}
