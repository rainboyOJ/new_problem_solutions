/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 分组背包
 */
#include <bits/stdc++.h>
using namespace std;

const int maxv = 1005;
int m, n;
vector<pair<int,int>> grp[105];
int dp[maxv];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> m >> n;
    int mxg = 0;
    for (int i = 1; i <= n; ++i) {
        int w, v, g;
        cin >> w >> v >> g;
        grp[g].push_back({w, v});
        mxg = max(mxg, g);
    }
    for (int g = 1; g <= mxg; ++g) {
        if (grp[g].empty()) continue;
        for (int j = m; j >= 0; --j) {
            for (auto &[w, v] : grp[g])
                if (j >= w)
                    dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
    cout << dp[m] << "\n";
    return 0;
}
