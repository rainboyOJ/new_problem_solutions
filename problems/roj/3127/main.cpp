/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 树链异或和恰为 k 的最少边数：点分治，best[d] 记录已处理部分中距离 d 的最少边数。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll INF = 1LL << 30; // 边数上界（简单路径最多 n-1 条边）

ll n, k;
ll edge_cnt = 0;

std::vector<int> head; // head[u] 是 u 的第一条弧
std::vector<int> nxt, eto, ewt;
std::vector<char> removed;
std::vector<ll> par, sz, dist, best;
std::vector<ll> touch2;

void add_edge(int u, int v, int w) {
    eto.push_back(v); ewt.push_back(w); nxt.push_back(head[u]); head[u] = edge_cnt++;
}

// 求 root 所在分量的重心：删掉它以后，剩下的每一块规模都不超过总量的一半
ll centroid_of(ll root) {
    par[root] = root;
    sz[root] = 0;
    std::vector<ll> order;
    order.push_back(root);
    for (size_t idx = 0; idx < order.size(); idx++) { // 边遍历边增长
        ll u = order[idx];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            ll v = eto[e];
            if (!removed[v] && v != par[u]) {
                par[v] = u;
                sz[v] = 0; // 先归零，倒序累加才是干净的
                order.push_back(v);
            }
        }
    }
    for (size_t idx = order.size(); idx-- > 0;) { // 子节点一定排在父节点后面
        ll u = order[idx];
        sz[u] += 1;
        if (u != root) sz[par[u]] += sz[u];
    }

    ll total = sz[root];
    ll cent = root;
    while (true) {
        ll heavy = -1, best_sub = 0;
        ll up = total - sz[cent]; // 父节点方向那一块的规模
        for (int e = head[cent]; e != -1; e = nxt[e]) {
            ll v = eto[e];
            if (!removed[v]) {
                ll sub = (v == par[cent]) ? up : sz[v];
                if (sub > best_sub) {
                    heavy = v;
                    best_sub = sub;
                }
            }
        }
        if (best_sub * 2 <= total) return cent; // 没有任何一块超过一半
        cent = heavy;
    }
}

// 点分治：返回边权和恰为 k 的简单路径的最少边数，不存在则返回 INF
ll min_edges() {
    removed.assign(n, 0);
    par.assign(n, 0);
    sz.assign(n, 0);
    dist.assign(n, 0);
    std::vector<ll> cnt(n, 0);
    best.assign(k + 1, INF); // best[d] = 已处理部分中距离为 d 的最少边数
    std::vector<ll> todo;
    todo.push_back(0);
    ll ans = INF;

    std::vector<ll> cur_dist;
    std::vector<ll> stack;

    while (!todo.empty()) {
        ll root = todo.back();
        todo.pop_back();
        if (removed[root]) continue; // 该点已在更早的层里当过重心
        ll cent = centroid_of(root);

        best[0] = 0; // 重心自身：距离 0，边数 0
        touch2.clear();
        touch2.push_back(0);
        for (int e = head[cent]; e != -1; e = nxt[e]) {
            ll v = eto[e];
            if (removed[v] || ewt[e] > k) continue; // 首边超过 k，整棵子树都凑不出 k
            // 扫描这棵子树：只看距离不超过 k 的点
            std::vector<ll> nodes;
            par[v] = cent;
            dist[v] = ewt[e];
            cnt[v] = 1;
            ll here = INF;
            stack.clear();
            stack.push_back(v);
            while (!stack.empty()) {
                ll u = stack.back();
                stack.pop_back();
                nodes.push_back(u);
                ll du = dist[u], cu = cnt[u];
                ll cand = cu + best[k - du]; // 与重心或更早的子树拼成经过重心的路径
                if (cand < here) here = cand;
                for (int e2 = head[u]; e2 != -1; e2 = nxt[e2]) {
                    ll x = eto[e2];
                    if (!removed[x] && x != par[u]) {
                        ll dx = du + ewt[e2];
                        if (dx <= k) { // 权值非负，更深的点只会更远，可整枝剪掉
                            par[x] = u;
                            dist[x] = dx;
                            cnt[x] = cu + 1;
                            stack.push_back(x);
                        }
                    }
                }
            }
            if (here < ans) ans = here;
            for (size_t t = 0; t < nodes.size(); t++) { // 本子树内部的两点留给更深层
                ll u = nodes[t];
                ll d = dist[u];
                if (cnt[u] < best[d]) {
                    if (best[d] == INF) touch2.push_back(d);
                    best[d] = cnt[u];
                }
            }
        }

        for (size_t t = 0; t < touch2.size(); t++) best[touch2[t]] = INF; // 只擦本层写过的格子
        removed[cent] = 1;
        for (int e = head[cent]; e != -1; e = nxt[e]) {
            if (!removed[eto[e]]) todo.push_back(eto[e]);
        }
    }
    return ans;
}

int main() {
    if (scanf("%lld %lld", &n, &k) != 2) return 0; // 空输入安全返回
    head.assign(n, -1);
    nxt.reserve(2 * n);
    eto.reserve(2 * n);
    ewt.reserve(2 * n);
    for (ll i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    ll ans = min_edges();
    printf("%lld\n", ans < INF ? ans : -1);
    return 0;
}
