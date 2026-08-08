#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int count_component(int start, int ban_u, int ban_v,
                    const vector<vector<int>> &g) {
    int n = (int)g.size() - 1;
    vector<int> vis(n + 1, 0);
    stack<int> st;
    st.push(start);
    vis[start] = 1;

    int cnt = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        ++cnt;

        for (int v : g[u]) {
            if ((u == ban_u && v == ban_v) || (u == ban_v && v == ban_u)) {
                continue;
            }
            if (!vis[v]) {
                vis[v] = 1;
                st.push(v);
            }
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Edge> edges;
    vector<vector<int>> g(n + 1);

    for (int i = 1; i <= n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        g[u].push_back(v);
        g[v].push_back(u);
    }

    long long ans = 0;
    for (const auto &e : edges) {
        // 直接删掉这条边，暴力数出一侧有多少点。
        int left_cnt = count_component(e.u, e.u, e.v, g);
        int right_cnt = n - left_cnt;
        ans += 1LL * e.w * llabs(1LL * left_cnt - right_cnt);
    }

    cout << ans << '\n';
    return 0;
}
