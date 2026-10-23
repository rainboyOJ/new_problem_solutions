/**
 * brute.cpp：基于期望离散定义的全路径枚举暴力解法
 * 
 * 为什么只适合小数据：
 * 本解法采用深度优先搜索，枚举所有从起点 1 到终点 n 的合法走法（简单路径）。
 * 在最坏情况下（例如完全分层 DAG），两点间的简单路径数量随节点数呈指数级爆炸（O(2^n)）。
 * 当 n 超过 20~30 时，递归搜索所有路径会引发严重的运行超时（TLE）。
 * 该暴力仅用于小规模数据下验证数学定义的正确性，并作为对拍的基准。
 * 
 * 浮点精度说明：
 * 采用 long double 进行高精度概率和路径长度累加，尽量减少中间阶段的大量乘除截断误差。
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long ll;

const int maxn = 100005;

struct Edge {
    int to;
    ll w;
};

int n, m;
vector<Edge> g[maxn];
int out_deg[maxn];

long double total_expected_len = 0.0;

// dfs 搜索所有从 1 到 n 的完整路径，累加路径概率与长度之积
void dfs(int u, long double curr_prob, long double curr_len) {
    if (u == n) {
        total_expected_len += curr_prob * curr_len;
        return;
    }
    
    for (const auto &e : g[u]) {
        long double next_prob = curr_prob / (long double)out_deg[u];
        dfs(e.to, next_prob, curr_len + (long double)e.w);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    if (!(cin >> n >> m)) return 0;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        out_deg[u]++;
    }
    
    dfs(1, 1.0L, 0.0L);
    
    cout << fixed << setprecision(2) << (double)total_expected_len << "\n";
    
    return 0;
}
