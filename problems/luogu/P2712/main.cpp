#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXP = 505;

int n;
int pos[MAXN];                    // pos[i] : 第 i 个摄像头所在的位置
vector<int> watch_pos[MAXN];      // watch_pos[i] : 第 i 个摄像头监视的地点
vector<int> cameras_at_pos[MAXP]; // cameras_at_pos[x] : 位置 x 上有哪些摄像头

struct TopologicalSort {
    int n;
    vector<vector<int>> graph;
    vector<int> indeg;

    explicit TopologicalSort(int n = 0) {
        init(n);
    }

    void init(int _n) {
        n = _n;
        graph.assign(n + 1, vector<int>());
        indeg.assign(n + 1, 0);
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        indeg[v]++;
    }

    // 不断删除入度为 0 的点，返回被删除的点数。
    int kahn_prune() {
        queue<int> q;
        vector<int> deg = indeg;
        int removed = 0;

        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            removed++;

            for (int v : graph[u]) {
                deg[v]--;
                if (deg[v] == 0) {
                    q.push(v);
                }
            }
        }

        return removed;
    }
};

TopologicalSort topo;

void read_input() {
    cin >> n;
    topo.init(n);

    for (int i = 0; i < MAXP; i++) {
        cameras_at_pos[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        watch_pos[i].clear();

        int m;
        cin >> pos[i] >> m;

        for (int j = 1; j <= m; j++) {
            int y;
            cin >> y;
            watch_pos[i].push_back(y);
        }

        cameras_at_pos[pos[i]].push_back(i);
    }
}

void build_graph() {
    for (int u = 1; u <= n; u++) {
        bool linked[MAXN] = {};

        for (int y : watch_pos[u]) {
            for (int v : cameras_at_pos[y]) {
                // 题目要求是“其他摄像头”，自己监视自己不算。
                if (v == u || linked[v]) {
                    continue;
                }
                linked[v] = true;
                topo.add_edge(u, v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_graph();

    int removed = topo.kahn_prune();
    cout << n - removed << '\n';

    return 0;
}
