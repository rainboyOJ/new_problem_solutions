/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:11
 * update_at: 2026-08-08 23:11
 */
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, V;
    cin >> N >> V;
    vector<int> a(N);
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    vector<int> dp(V + 1);
    dp[0] = 1;
    for (int c = 1; c <= V; ++c) {
        for (int v : a) {
            if (c >= v)
                dp[c] = (dp[c] + dp[c - v]) % MOD;
        }
    }
    cout << dp[V] << '\n';
    return 0;
}
