/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:11
 * update_at: 2026-08-08 23:11
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, V;
    cin >> N >> V;
    vector<int> dp(V + 1);
    for (int i = 0; i < N; ++i) {
        int v, w;
        cin >> v >> w;
        for (int c = V; c >= v; --c)
            dp[c] = max(dp[c], dp[c - v] + w);
    }
    cout << dp[V] << '\n';
    return 0;
}
