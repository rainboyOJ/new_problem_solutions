/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:05
 * update_at: 2026-11-11 00:05
 */

// brute.cpp：小数据暴力枚举军营与看守边，验证连通性
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int n, m;
vector<pair<int, int>> edges;

int p[20];
int find_set(int x) {
    return p[x] == x ? x : (p[x] = find_set(p[x]));
}

bool check(int node_mask, int edge_mask, int cut_edge) {
    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 0; i < m; ++i) {
        if (i == cut_edge) continue; // 这条边被切断
        // 这条边被保留的条件：看守了，或者没被切断
        // 注意：敌方袭击任意一条未被看守的边 cut_edge，看守边不会被切断
        // 所以当 i != cut_edge 时该边仍在；如果 i 被看守，即使被袭击也不会断
        // 简而言之：若 i 被切断，则 i 必须是未看守的边
        p[find_set(edges[i].first)] = find_set(edges[i].second);
    }
    // 检查所有在 node_mask 中的点是否在同一连通块
    int root = -1;
    for (int i = 0; i < n; ++i) {
        if ((node_mask >> i) & 1) {
            int u = i + 1;
            if (root == -1) root = find_set(u);
            else if (find_set(u) != root) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int ans = 0;
    // 枚举军营集合（非空）
    for (int node_mask = 1; node_mask < (1 << n); ++node_mask) {
        // 枚举看守边集合
        for (int edge_mask = 0; edge_mask < (1 << m); ++edge_mask) {
            bool ok = true;
            // 敌方袭击任意一条未看守的边
            for (int i = 0; i < m; ++i) {
                if (!((edge_mask >> i) & 1)) { // 未被看守
                    if (!check(node_mask, edge_mask, i)) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) ans = (ans + 1) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
