// brute.cpp：枚举删掉哪一条边，然后直接检查每个连通块是否同时拥有 A/B 两种服务。
// 这是最贴近题意的暴力验证版，只适合小数据对拍。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
} edges[105];

int n, m, cnt_a, cnt_b;
bool has_a[25], has_b[25];
vector<int> g[25];
bool vis[25];

void build_graph(int ban) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = false;
    }

    for (int i = 1; i <= m; i++) {
        if (i == ban) {
            continue;
        }
        int u = edges[i].u;
        int v = edges[i].v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void dfs(int u, int &cnt_node, int &cnt_service_a, int &cnt_service_b) {
    vis[u] = true;
    cnt_node++;
    cnt_service_a += has_a[u];
    cnt_service_b += has_b[u];

    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!vis[v]) {
            dfs(v, cnt_node, cnt_service_a, cnt_service_b);
        }
    }
}

bool is_critical(int ban) {
    build_graph(ban);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int cnt_node = 0;
            int cnt_service_a = 0;
            int cnt_service_b = 0;
            dfs(i, cnt_node, cnt_service_a, cnt_service_b);

            if (cnt_service_a == 0 || cnt_service_b == 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> cnt_a >> cnt_b;

    memset(has_a, 0, sizeof(has_a));
    memset(has_b, 0, sizeof(has_b));

    for (int i = 1; i <= cnt_a; i++) {
        int x;
        cin >> x;
        has_a[x] = true;
    }
    for (int i = 1; i <= cnt_b; i++) {
        int x;
        cin >> x;
        has_b[x] = true;
    }

    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    vector<int> answer;
    for (int i = 1; i <= m; i++) {
        if (is_critical(i)) {
            answer.push_back(i);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        int id = answer[i];
        cout << edges[id].u << ' ' << edges[id].v << '\n';
    }

    return 0;
}
