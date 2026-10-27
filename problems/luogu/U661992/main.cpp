/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * 多重背包问题 I — N≤100 V≤100 s_i≤100，直接三重循环DP
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, V;
int dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> V;
    for (int i = 1; i <= n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        for (int c = V; c >= 0; --c)
            for (int k = 1; k <= s && k * v <= c; ++k)
                dp[c] = max(dp[c], dp[c - k * v] + k * w);
    }
    cout << dp[V] << '\n';
    return 0;
}
