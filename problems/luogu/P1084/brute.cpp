/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:05
 * update_at: 2026-11-10 23:05
 */

// brute.cpp：在小数据下用纯暴力验证（在小规模树上检验 check 逻辑）
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAXN = 1005;
struct Edge {
    int to;
    int weight;
};

vector<Edge> tree[MAXN];
int army[MAXN];
bool has_army[MAXN];

int parent_node[MAXN];
ll parent_dist[MAXN];

void get_parent(int u, int fa, ll w) {
    parent_node[u] = fa;
    parent_dist[u] = w;
    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        get_parent(e.to, u, e.weight);
    }
}

bool dfs_leaf(int u, int fa) {
    if (has_army[u]) return true;
    bool is_leaf = true;
    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        is_leaf = false;
        if (!dfs_leaf(e.to, u)) return false;
    }
    if (is_leaf) return false;
    return true;
}

bool check(ll mid, int n, int m) {
    for (int i = 1; i <= n; ++i) has_army[i] = false;

    vector<pair<ll, int>> rest_armies; // (rest_time, root_son)
    for (int i = 1; i <= m; ++i) {
        int u = army[i];
        ll cur = mid;
        while (parent_node[u] > 1 && parent_dist[u] <= cur) {
            cur -= parent_dist[u];
            u = parent_node[u];
        }
        if (parent_node[u] == 1 && parent_dist[u] <= cur) {
            rest_armies.push_back({cur - parent_dist[u], u});
        } else {
            has_army[u] = true;
        }
    }

    vector<pair<ll, int>> sons; // (dist, id)
    for (const auto& e : tree[1]) {
        if (!dfs_leaf(e.to, 1)) {
            sons.push_back({e.weight, e.to});
        }
    }

    sort(rest_armies.begin(), rest_armies.end());
    vector<bool> used(rest_armies.size(), false);

    vector<pair<ll, int>> uncovered;
    for (const auto& son : sons) {
        int best_idx = -1;
        for (size_t i = 0; i < rest_armies.size(); ++i) {
            if (!used[i] && rest_armies[i].second == son.second) {
                best_idx = i;
                break;
            }
        }
        if (best_idx != -1 && rest_armies[best_idx].first < 2 * son.first) {
            used[best_idx] = true;
        } else {
            uncovered.push_back(son);
        }
    }

    vector<ll> free_a;
    for (size_t i = 0; i < rest_armies.size(); ++i) {
        if (!used[i]) free_a.push_back(rest_armies[i].first);
    }
    sort(uncovered.begin(), uncovered.end());

    size_t ptr = 0;
    for (const auto& s : uncovered) {
        while (ptr < free_a.size() && free_a[ptr] < s.first) ptr++;
        if (ptr == free_a.size()) return false;
        ptr++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    ll total_w = 0;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
        total_w += w;
    }
    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> army[i];

    get_parent(1, 0, 0);

    if (m < static_cast<int>(tree[1].size())) {
        cout << -1 << "\n";
        return 0;
    }

    ll l = 0, r = total_w, ans = -1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (check(mid, n, m)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
    return 0;
}
