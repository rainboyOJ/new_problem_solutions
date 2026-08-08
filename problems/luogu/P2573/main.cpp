#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 1000005;

struct Edge {
    int u, v, w;
} edges[MAXM];

struct SortEdge {
    int u, v, w, low_h;

    bool operator<(const SortEdge &other) const {
        if (low_h != other.low_h) {
            return low_h > other.low_h;
        }
        return w < other.w;
    }
};

int n, m;
int h[MAXN];
vector<pair<int, int>> g[MAXN];
bool reachable[MAXN];
int fa[MAXN];

void dfs(int start) {
    stack<int> st;
    st.push(start);
    reachable[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (pair<int, int> e : g[u]) {
            int v = e.first;
            if (reachable[v]) {
                continue;
            }
            reachable[v] = true;
            st.push(v);
        }
    }
}

void init_dsu() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }
    fa[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<SortEdge> cand;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (h[u] >= h[v]) {
            g[u].push_back({v, w});
        }
        if (h[v] >= h[u]) {
            g[v].push_back({u, w});
        }
    }

    dfs(1);

    int reachable_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (reachable[i]) {
            reachable_cnt++;
        }
    }

    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (!reachable[u] || !reachable[v]) {
            continue;
        }
        cand.push_back({u, v, w, min(h[u], h[v])});
    }

    sort(cand.begin(), cand.end());

    init_dsu();
    long long answer = 0;
    int used = 0;

    for (SortEdge e : cand) {
        if (!unite(e.u, e.v)) {
            continue;
        }
        answer += e.w;
        used++;
        if (used == reachable_cnt - 1) {
            break;
        }
    }

    cout << reachable_cnt << ' ' << answer << '\n';

    return 0;
}
