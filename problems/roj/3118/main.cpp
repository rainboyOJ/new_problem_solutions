/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 树中点对距离：点分治 + 「汇总减各子树」容斥，统计距离不超过 k 的点对。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

ll N, K;

std::vector<std::vector<int> > g; // g[u]：u 出发的边编号
std::vector<int> eto, ewt;        // 边的另一端与边权
std::vector<char> removed;
std::vector<int> parent;
std::vector<ll> sz;
std::vector<ll> dists;            // 扫描子树时收集的距离
std::vector<int> order;

void add_edge(int u, int v, int w) {
    eto.push_back(v); ewt.push_back(w); g[u].push_back((int)eto.size() - 1);
    eto.push_back(u); ewt.push_back(w); g[v].push_back((int)eto.size() - 1);
}

// 求 root 所在分量的重心：删掉它后，剩下的每块规模都不超过总量一半
int find_centroid(int root) {
    int n = (int)g.size();
    parent.assign(n, -1);
    parent[root] = root;
    order.clear();
    order.push_back(root);
    for (size_t idx = 0; idx < order.size(); idx++) { // 边遍历边增长，等价于手写栈
        int u = order[idx];
        for (size_t j = 0; j < g[u].size(); j++) {
            int e = g[u][j];
            int v = eto[e];
            if (!removed[v] && v != parent[u]) {
                parent[v] = u;
                order.push_back(v);
            }
        }
    }

    for (size_t idx = order.size(); idx-- > 0;) { // 子节点一定排在父节点之后
        int u = order[idx];
        sz[u] = 1;
        for (size_t j = 0; j < g[u].size(); j++) {
            int e = g[u][j];
            int v = eto[e];
            if (!removed[v] && parent[v] == u) sz[u] += sz[v];
        }
    }

    int cent = root;
    ll total = sz[root];
    while (true) {
        int heavy = -1;
        ll best = 0;
        for (size_t j = 0; j < g[cent].size(); j++) {
            int e = g[cent][j];
            int v = eto[e];
            if (!removed[v] && parent[v] == cent && sz[v] > best) {
                heavy = v;
                best = sz[v];
            }
        }
        if (heavy < 0 || best * 2 <= total) return cent;
        cent = heavy;
    }
}

// 统计有序数组里有多少对 j <= i 满足 dist[j] + dist[i] <= k（含 i = j 的自配对）
ll count_le(std::vector<ll>& d, ll k) {
    ll total = 0;
    for (size_t i = 0; i < d.size(); i++) {
        ll lim = k - d[i];
        total += std::upper_bound(d.begin(), d.begin() + i + 1, lim) - d.begin();
    }
    return total;
}

ll divide() {
    int n = (int)g.size();
    removed.assign(n, 0);
    parent.assign(n, 0);
    sz.assign(n, 0);
    std::vector<int> roots;
    roots.push_back(0);
    ll answer = 0;

    while (!roots.empty()) {
        int root = roots.back();
        roots.pop_back();
        if (removed[root]) continue; // 该点已在更早的层里当过重心

        int cent = find_centroid(root);

        // 从重心出发按子树收集距离（大于 k 的分支剪掉），sub[0] 是空占位（重心自身）
        std::vector<std::vector<ll> > sub;
        sub.push_back(std::vector<ll>());
        for (size_t j = 0; j < g[cent].size(); j++) {
            int e = g[cent][j];
            int v = eto[e];
            if (removed[v]) continue;
            std::vector<std::pair<int, std::pair<int, ll> > > stk;
            dists.clear();
            stk.push_back(std::make_pair(v, std::make_pair(cent, (ll)ewt[e])));
            while (!stk.empty()) {
                int u = stk.back().first;
                int par = stk.back().second.first;
                ll d = stk.back().second.second;
                stk.pop_back();
                if (d > K) continue; // 权值非负，更深的点只会更远
                dists.push_back(d);
                for (size_t t = 0; t < g[u].size(); t++) {
                    int e2 = g[u][t];
                    int x = eto[e2];
                    if (x != par && !removed[x]) { // 只看本子树 DFS 的父节点
                        stk.push_back(std::make_pair(x, std::make_pair(u, d + ewt[e2])));
                    }
                }
            }
            std::sort(dists.begin(), dists.end());
            sub.push_back(dists);
        }

        std::vector<ll> merged;
        merged.push_back(0);
        for (size_t s = 1; s < sub.size(); s++) {
            for (size_t t = 0; t < sub[s].size(); t++) merged.push_back(sub[s][t]);
        }
        std::sort(merged.begin(), merged.end());
        answer += count_le(merged, K);
        for (size_t s = 1; s < sub.size(); s++) {
            answer -= count_le(sub[s], K); // 同一子树内部的配对要在本层扣掉
        }

        removed[cent] = 1; // 删掉重心，邻居各代表一个新分量
        for (size_t j = 0; j < g[cent].size(); j++) {
            int e = g[cent][j];
            int v = eto[e];
            if (!removed[v]) roots.push_back(v);
        }
    }
    return answer;
}

int main() {
    std::vector<ll> out;
    while (scanf("%lld %lld", &N, &K) == 2) {
        if (N == 0 && K == 0) break;
        g.assign(N, std::vector<int>());
        eto.clear();
        ewt.clear();
        for (ll i = 0; i < N - 1; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add_edge(u, v, w);
        }
        // 计数包含 x = y 的自配对，而路径要求两个节点不同，故每个点各减一次
        out.push_back(divide() - N);
    }
    for (size_t i = 0; i < out.size(); i++) {
        printf("%lld\n", out[i]);
    }
    return 0;
}
