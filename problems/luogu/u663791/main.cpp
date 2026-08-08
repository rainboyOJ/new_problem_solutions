/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * 多重背包问题 II — 二进制分组优化
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int n, V;
int dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> V;
    for (int i = 1; i <= n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        for (int k = 1; s > 0; k <<= 1) {
            int cnt = min(k, s);
            s -= cnt;
            int pack_v = cnt * v;
            int pack_w = cnt * w;
            for (int c = V; c >= pack_v; --c)
                dp[c] = max(dp[c], dp[c - pack_v] + pack_w);
        }
    }
    cout << dp[V] << '\n';
    return 0;
}
