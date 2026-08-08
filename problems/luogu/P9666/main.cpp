#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400005;
const int MAXM = 800005;

int T;
int n, m;

int fa[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], edge_id[MAXM], edge_cnt;
int parent_node[MAXN], parent_edge[MAXN];
bool vis[MAXN];

void init_graph(int n) {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        head[i] = 0;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

void unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x != y) {
        fa[x] = y;
    }
}

void add_edge(int u, int v, int id) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_id[edge_cnt] = id;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

vector<int> find_path_edges(int start, int target) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
        parent_node[i] = 0;
        parent_edge[i] = 0;
    }

    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target) {
            break;
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            parent_node[v] = u;
            parent_edge[v] = edge_id[i];
            q.push(v);
        }
    }

    vector<int> path_edges;
    int cur = target;
    while (cur != start) {
        path_edges.push_back(parent_edge[cur]);
        cur = parent_node[cur];
    }
    return path_edges;
}

void solve_one_case() {
    cin >> n >> m;
    init_graph(n);

    int cycle_u = 0;
    int cycle_v = 0;
    int cycle_edge = 0;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        if (cycle_edge != 0) {
            continue;
        }

        if (find_root(u) == find_root(v)) {
            cycle_u = u;
            cycle_v = v;
            cycle_edge = i;
            continue;
        }

        unite(u, v);
        add_edge(u, v, i);
        add_edge(v, u, i);
    }

    if (cycle_edge == 0) {
        cout << -1 << '\n';
        return;
    }

    vector<int> answer = find_path_edges(cycle_u, cycle_v);
    answer.push_back(cycle_edge);
    sort(answer.begin(), answer.end());

    for (int i = 0; i < (int)answer.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one_case();
    }

    return 0;
}
