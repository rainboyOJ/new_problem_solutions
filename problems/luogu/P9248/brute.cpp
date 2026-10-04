/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 18:25
 */
// P9248 暴力对拍解：直接按题意枚举。
//
// 1. 枚举所有非空点集（生成器保证 N <= 15），筛出连通且重量和 <= M 的。
// 2. 求最大点权和 V*，把点权和等于 V* 的集合记为完美集合。
// 3. 对每个完美集合 S 求出它的合法测试点集合（x ∈ S 且对 S 内每点 y
//    有 dist(x,y)*v_y <= Max）。
// 4. 暴力枚举完美集合中所有 C(|P|, K) 种 K 元选择，检查是否存在一个点
//    同时出现在这 K 个集合的合法测试点集合里。
//
// 只适用于 K 很小、|P| 很小的对拍数据（生成器保证 K <= 4、|P| <= 60）。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long u64;

static const u64 MOD = 11920928955078125ULL;

static int N, M;
static ll K, Max;
static ll w[64], v[64];
static ll dist_[64][64];
static vector<pair<int,ll>> g[64];

int main() {
    scanf("%d %d %lld %lld", &N, &M, &K, &Max);
    for (int i = 0; i < N; i++) scanf("%lld", &w[i]);
    for (int i = 0; i < N; i++) scanf("%lld", &v[i]);
    for (int i = 0; i < N - 1; i++) {
        int a, b; ll c;
        scanf("%d %d %lld", &a, &b, &c);
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    const ll INF = (ll)4e18;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) dist_[i][j] = (i == j ? 0 : INF);
        // BFS 求单源最短路（边权非负）
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
        dist_[i][i] = 0; pq.push({0, i});
        while (!pq.empty()) {
            auto pr = pq.top(); pq.pop();
            int u = pr.second; ll d = pr.first;
            if (d > dist_[i][u]) continue;
            for (auto &e : g[u]) {
                int to = e.first; ll nd = d + e.second;
                if (nd < dist_[i][to]) { dist_[i][to] = nd; pq.push({nd, to}); }
            }
        }
    }

    // 枚举所有非空子集
    vector<int> perf;          // 完美集合的 bitmask
    ll Vstar = -1;
    int total = 1 << N;
    for (int mask = 1; mask < total; mask++) {
        ll sw = 0, sv = 0;
        for (int i = 0; i < N; i++) if (mask >> i & 1) { sw += w[i]; sv += v[i]; }
        if (sw > M) continue;
        // 连通性：BFS
        int start = -1;
        for (int i = 0; i < N; i++) if (mask >> i & 1) { start = i; break; }
        int seen = 0;
        vector<int> stk = { start };
        vector<bool> vis(N, false);
        vis[start] = true;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back(); seen++;
            for (auto &e : g[u]) {
                int to = e.first;
                if ((mask >> to & 1) && !vis[to]) { vis[to] = true; stk.push_back(to); }
            }
        }
        if (seen != __builtin_popcount((unsigned)mask)) continue;
        if (sv > Vstar) { Vstar = sv; perf.clear(); perf.push_back(mask); }
        else if (sv == Vstar) perf.push_back(mask);
    }

    if (Vstar < 0 || (ll)perf.size() < K || K < 1) { puts("0"); return 0; }

    // 每个完美集合的合法测试点
    int P = perf.size();
    vector<int> app(P, 0);
    for (int t = 0; t < P; t++) {
        int m = perf[t];
        for (int x = 0; x < N; x++) {
            if (!(m >> x & 1)) continue;
            bool ok = true;
            for (int y = 0; y < N; y++) {
                if (!(m >> y & 1)) continue;
                if (dist_[x][y] * v[y] > Max) { ok = false; break; }
            }
            if (ok) app[t] |= (1 << x);
        }
    }

    // 暴力枚举 K 元组合，检查是否存在公共测试点
    u64 ans = 0;
    vector<int> idx;
    function<void(int,int)> dfs = [&](int pos, int last) {
        if ((int)idx.size() == K) {
            int inter = app[idx[0]];
            for (int j = 1; j < K; j++) inter &= app[idx[j]];
            if (inter) ans = (ans + 1) % MOD;
            return;
        }
        for (int j = last + 1; j < P; j++) {
            idx.push_back(j);
            dfs(pos + 1, j);
            idx.pop_back();
        }
    };
    dfs(0, -1);
    printf("%llu\n", ans % MOD);
    return 0;
}
