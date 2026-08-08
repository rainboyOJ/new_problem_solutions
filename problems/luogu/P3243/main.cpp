#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;

int T;
int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], indeg[MAXN], edge_cnt;
int ans[MAXN];

// 在反图上加一条 u -> v 的边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    indeg[v]++;
}

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        indeg[i] = 0;
    }
}

bool solve_case() {
    priority_queue<int> pq; // 反图里每次优先取编号最大的点

    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            pq.push(i);
        }
    }

    int tot = 0;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        ans[++tot] = u;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            indeg[v]--;
            if (indeg[v] == 0) {
                pq.push(v);
            }
        }
    }

    if (tot != n) {
        return false;
    }

    for (int i = n; i >= 1; i--) {
        cout << ans[i];
        if (i > 1) {
            cout << ' ';
        }
    }
    cout << '\n';
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m;
        init_graph();

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            // 原图要求 u 在 v 前面，因此在反图上连 v -> u。
            add_edge(v, u);
        }

        if (!solve_case()) {
            cout << "Impossible!\n";
        }
    }

    return 0;
}
