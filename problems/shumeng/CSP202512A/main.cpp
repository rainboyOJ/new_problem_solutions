/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:04
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> value(n + 1); // 序列 a[1..n]
    for (int i = 1; i <= n; i++) cin >> value[i];

    // 读入所有 S 集合，同时计算每个集合的异或值
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

    // 读入所有 T 集合，同时计算每个集合的异或值
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

    // 输入保证集合内元素严格递增，vector 直接比较即可得到集合是否相等
    for (int i = 0; i < m; i++) {
        bool same_set = s[i] == t[i];      // 真实的相等结论
        bool same_xor = sx[i] == tx[i];    // 小 C 用异或判断的结论
        cout << (same_set == same_xor ? "correct" : "wrong") << '\n';
    }
    return 0;
}
