/**
 * brute.cpp：小数据/低天数暴力解（按天数动态规划），用于帮助理解题意与对拍。
 * 为什么只适合小数据：
 * 朴素 DP 外层需要枚举每一天 t 从 1 到 T，内层枚举所有有向边，
 * 时间复杂度为 O(T * m)。
 * 当 T <= 50000 时能在 1 秒内运行完毕（覆盖前 40% 数据），
 * 但当 T 达到 10^9 时，循环次数高达 10^9 * 500 = 5 * 10^11，会严重超时（TLE）。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 55;
const int MAXM = 505;
const int MAXK = 205;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m, k;
ll T;
ll c[MAXN];

struct Edge {
    int u, v;
    int w;
} edges[MAXM];

struct Festival {
    ll t;
    int x;
    ll y;
} fest[MAXK];

// dp[t % 6][u]：到达城市 u，距离恰好还剩多久到达的记录；
// 这里直接用二维 vector dp[t][u] 支持 T <= 100000 的情况
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> T >> k)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    for (int i = 1; i <= k; ++i) {
        cin >> fest[i].t >> fest[i].x >> fest[i].y;
    }

    // 预处理美食节哈希或查找表：小数据下可以用 map<(t, x), y>
    map<pair<ll, int>, ll> fest_map;
    for (int i = 1; i <= k; ++i) {
        fest_map[{fest[i].t, fest[i].x}] += fest[i].y;
    }

    // dp[t][u]：第 t 天恰好到达城市 u 的最大愉悦值
    // 为节省空间，只记录最近 6 天的状态 dp[0..5][u]
    vector<vector<ll>> dp(6, vector<ll>(n + 1, -INF));
    dp[0][1] = c[1];

    for (ll t = 1; t <= T; ++t) {
        int cur = t % 6;
        for (int i = 1; i <= n; ++i) {
            dp[cur][i] = -INF;
        }

        for (int i = 1; i <= m; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (t >= w) {
                int prev = (t - w) % 6;
                if (dp[prev][u] >= 0) {
                    ll val = dp[prev][u] + c[v];
                    if (val > dp[cur][v]) {
                        dp[cur][v] = val;
                    }
                }
            }
        }

        // 检查第 t 天是否有美食节
        for (int i = 1; i <= n; ++i) {
            if (dp[cur][i] >= 0) {
                auto it = fest_map.find({t, i});
                if (it != fest_map.end()) {
                    dp[cur][i] += it->second;
                }
            }
        }
    }

    ll ans = dp[T % 6][1];
    if (ans < 0) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
