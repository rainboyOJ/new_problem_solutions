/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:00
 * update_at: 2026-10-08 20:00
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;    // n <= 300，多留几个
const int MAXM = 50000;  // m <= n(n-1)/2 = 44850

struct Edge {
    ll u;
    ll v;
    ll w;
};

Edge edge[MAXM];       // 边表，1..m 存放题目给的 m 条边
ll parent_node[MAXN];  // 并查集父节点，parent_node[i] == i 表示 i 是所在连通块的根

// 按边权升序，供 sort 使用（不用 lambda）
bool cmp_edge(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

// 路径压缩查找 x 所在连通块的根
ll find_set(ll x) {
    while (parent_node[x] != x) {
        parent_node[x] = parent_node[parent_node[x]];
        x = parent_node[x];
    }
    return x;
}

void solve() {
    ll n, m;
    if (!(cin >> n >> m)) {
        return;
    }
    for (ll i = 1; i <= m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }

    // Kruskal：边权升序贪心，能连通就选
    sort(edge + 1, edge + m + 1, cmp_edge);

    for (ll i = 1; i <= n; i++) {
        parent_node[i] = i;
    }

    ll chosen = 0;     // 已选边数，连通后恰好是 n-1
    ll bottleneck = 0; // 已选边中的最大边权
    for (ll i = 1; i <= m; i++) {
        ll root_u = find_set(edge[i].u);
        ll root_v = find_set(edge[i].v);
        if (root_u == root_v) {
            continue;
        }
        parent_node[root_u] = root_v;
        chosen++;
        bottleneck = edge[i].w; // 边已升序，最后加入的边权就是最大值，无需再比较
        if (chosen == n - 1) {
            break;
        }
    }

    cout << chosen << " " << bottleneck << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
