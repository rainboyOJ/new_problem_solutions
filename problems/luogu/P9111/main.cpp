#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll NEG_INF = -(1LL << 60);
const int MAXN = 405;

int n;
ll d[MAXN];
vector<int> g[MAXN];
vector<int> child[MAXN];
vector<int> order_nodes;

// states[u][c] = 若干个 (W, F)
// c : 在子树 u 中，从 u 出发沿定向边能到达的点数
// W : 能通过反向链路汇总到 u 的总权值
// F : 这棵子树内部的总答案
vector<vector<pair<ll, ll> > > states[MAXN];

void dfs_build(int u, int fa) {
    order_nodes.push_back(u);
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        child[u].push_back(v);
        dfs_build(v, u);
    }
}

// 固定同一个 c 时，保留 (W, F) 的 Pareto 前沿。
// 如果存在另一个状态同时满足 W 更大且 F 更大，那么当前状态以后不可能更优。
vector<pair<ll, ll> > prune_same_c(vector<pair<ll, ll> > vec) {
    sort(vec.begin(), vec.end(), [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second > b.second;
    });

    vector<pair<ll, ll> > res;
    ll best_f = NEG_INF;
    int i = 0;
    while (i < (int) vec.size()) {
        int j = i;
        ll cur_w = vec[i].first;
        ll best_this_w = NEG_INF;
        while (j < (int) vec.size() && vec[j].first == cur_w) {
            best_this_w = max(best_this_w, vec[j].second);
            j++;
        }
        if (best_this_w > best_f) {
            res.push_back(make_pair(cur_w, best_this_w));
            best_f = best_this_w;
        }
        i = j;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 2; i <= n; i++) {
        int c;
        cin >> c;
        g[i].push_back(c);
        g[c].push_back(i);
    }

    dfs_build(1, 0);

    for (int idx = (int) order_nodes.size() - 1; idx >= 0; idx--) {
        int u = order_nodes[idx];

        // dp[c]：当前已经合并完若干个儿子后，能形成的 (W, F) 前沿。
        vector<vector<pair<ll, ll> > > dp(2);
        dp[1].push_back(make_pair(d[u], d[u]));

        for (int v : child[u]) {
            vector<vector<pair<ll, ll> > > ndp((int) dp.size() + (int) states[v].size());

            for (int cu = 1; cu < (int) dp.size(); cu++) {
                if (dp[cu].empty()) {
                    continue;
                }
                for (pair<ll, ll> now : dp[cu]) {
                    ll wu = now.first;
                    ll fu = now.second;
                    for (int cv = 1; cv < (int) states[v].size(); cv++) {
                        if (states[v][cv].empty()) {
                            continue;
                        }
                        for (pair<ll, ll> son : states[v][cv]) {
                            ll wv = son.first;
                            ll fv = son.second;

                            // 方案 1：v -> u
                            // 子树 v 的权值能汇到 u，u 的可达点数不变。
                            ndp[cu].push_back(make_pair(
                                wu + wv,
                                fu + fv + wv * cu
                            ));

                            // 方案 2：u -> v
                            // u 能继续走进 v 子树，u 的可达点数增加 cv。
                            ndp[cu + cv].push_back(make_pair(
                                wu,
                                fu + fv + wu * cv
                            ));
                        }
                    }
                }
            }

            for (int c = 1; c < (int) ndp.size(); c++) {
                if (!ndp[c].empty()) {
                    ndp[c] = prune_same_c(ndp[c]);
                }
            }
            dp.swap(ndp);
        }

        states[u].swap(dp);
    }

    ll ans = NEG_INF;
    for (int c = 1; c < (int) states[1].size(); c++) {
        for (pair<ll, ll> st : states[1][c]) {
            ans = max(ans, st.second);
        }
    }

    cout << ans << '\n';
    return 0;
}
