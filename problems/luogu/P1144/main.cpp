#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 2000005;
const int MOD = 100003;

int n, m;
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edge_cnt;
int dist_node[MAXN];
int ways[MAXN];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
}

void bfs() {
    for (int i = 1; i <= n; i++) {
        dist_node[i] = -1;
        ways[i] = 0;
    }

    queue<int> que;
    dist_node[1] = 0;
    ways[1] = 1;
    que.push(1);

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (dist_node[v] == -1) {
                dist_node[v] = dist_node[u] + 1;
                ways[v] = ways[u];
                que.push(v);
            } else if (dist_node[v] == dist_node[u] + 1) {
                ways[v] += ways[u];
                if (ways[v] >= MOD) {
                    ways[v] %= MOD;
                }
            }
        }
    }
}

void solve() {
    bfs();
    for (int i = 1; i <= n; i++) {
        cout << ways[i] % MOD << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
