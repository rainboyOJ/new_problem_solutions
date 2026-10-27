/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * 多重背包问题 III — 单调队列优化
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 50005;
int n, V;
int dp[maxn], g[maxn];
int q[maxn], head, tail;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> V;
    for (int i = 1; i <= n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        memcpy(g, dp, sizeof(dp));
        for (int r = 0; r < v; ++r) {
            head = 0, tail = 0;
            for (int k = 0; r + k * v <= V; ++k) {
                int idx = r + k * v;
                int val = g[idx] - k * w;
                while (head < tail && q[head] < k - s) ++head;
                while (head < tail && g[r + q[tail - 1] * v] - q[tail - 1] * w <= val) --tail;
                q[tail++] = k;
                dp[idx] = g[r + q[head] * v] + (k - q[head]) * w;
            }
        }
    }
    cout << dp[V] << '\n';
    return 0;
}
