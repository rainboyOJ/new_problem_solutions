#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;
const int MAXM = 50000 * 2 + 5;
const int INF = 1e9;

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int dist_arr[MAXN];

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        dist_arr[i] = INF;
    }
}

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void bfs(int start) {
    queue<int> q;
    dist_arr[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dist_arr[v] != INF) {
                continue;
            }

            dist_arr[v] = dist_arr[u] + 1;
            q.push(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph();

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    bfs(1);

    int best_id = 1;
    int best_dist = -1;
    int count = 0;

    for (int i = 1; i <= n; i++) {
        if (dist_arr[i] > best_dist) {
            best_dist = dist_arr[i];
            best_id = i;
            count = 1;
        }
        else if (dist_arr[i] == best_dist) {
            count++;
        }
    }

    cout << best_id << ' ' << best_dist << ' ' << count << '\n';

    return 0;
}
