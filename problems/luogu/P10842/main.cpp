/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 16:10
 */
// P10842 【MX-J2-T3】Piggy and Trees
// 结论：答案 = D * (n-2) / 2，其中 D 是所有点对距离之和。
// D = sum(每条边 size * (n - size))，一遍 DFS 求子树大小即可。
// 推导：dis(u,x)+dis(v,x)=dis(u,v) 当且仅当 x 在 u-v 路径上，
// f(u,v,i) = i 到 u-v 路径的距离 = (dis(i,u)+dis(i,v)-dis(u,v))/2。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const long long MOD = 1e9 + 7;

int n;
vector<int> g[MAXN]; // 树的邻接表
int sz[MAXN];        // sz[u]：以 u 为根的子树大小
long long D;         // 所有点对距离之和

// 求子树大小（dfs 遍历，仿 rbook 模板 dfs-traversal）。
void dfs(int u, int fa) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        // 边 (u, v) 把树分成大小为 sz[v] 和 n - sz[v] 的两部分
        D = (D + (long long)sz[v] * (n - sz[v])) % MOD;
    }
}

// 快速幂：求 a^b mod MOD。
long long quick_pow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    // 答案 = D * (n-2) / 2 = D * (n-2) * inv(2) mod MOD
    long long inv2 = quick_pow(2, MOD - 2);
    long long ans = D * ((n - 2 + MOD) % MOD) % MOD * inv2 % MOD;
    cout << ans << '\n';

    return 0;
}
