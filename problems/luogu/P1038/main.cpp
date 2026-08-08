#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
long long c[MAXN];   // c[i] : 神经元 i 当前状态
long long u_[MAXN];  // u_[i] : 神经元 i 的阈值
int outdeg[MAXN];

struct Edge {
    int to;
    long long w;
};

vector<Edge> graph[MAXN];
int indeg[MAXN];

void read_input() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> u_[i];
        graph[i].clear();
        indeg[i] = 0;
        outdeg[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        indeg[v]++;
        outdeg[u]++;
    }

    // 输入层的状态已经直接给出，只有非输入层需要先减去阈值。
    for (int i = 1; i <= n; i++) {
        if (indeg[i] > 0) {
            c[i] -= u_[i];
        }
    }
}

void solve() {
    queue<int> q;
    int deg[MAXN];
    memcpy(deg, indeg, sizeof(indeg));

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (Edge e : graph[u]) {
            int v = e.to;

            // 只有兴奋状态的神经元才会向后传递信号。
            if (c[u] > 0) {
                c[v] += c[u] * e.w;
            }

            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    bool has_answer = false;
    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0 && c[i] > 0) {
            cout << i << ' ' << c[i] << '\n';
            has_answer = true;
        }
    }

    if (!has_answer) {
        cout << "NULL\n";
    }

    return 0;
}
