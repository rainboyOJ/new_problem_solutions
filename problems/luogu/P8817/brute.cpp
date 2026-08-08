// brute.cpp：小数据暴力解，枚举 4 个不同景点并检查 5 段行程是否可达。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, m, k;
long long score[MAXN];
vector<int> graph_edges[MAXN];
bool can_reach[MAXN][MAXN];

void bfs(int start) {
    int dist[MAXN];
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] > k + 1) {
            continue;
        }
        can_reach[start][u] = true;
        if (dist[u] == k + 1) {
            continue;
        }
        for (int i = 0; i < (int)graph_edges[u].size(); i++) {
            int v = graph_edges[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 2; i <= n; i++) {
        cin >> score[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph_edges[u].push_back(v);
        graph_edges[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    long long answer = 0;
    for (int a = 2; a <= n; a++) {
        for (int b = 2; b <= n; b++) {
            for (int c = 2; c <= n; c++) {
                for (int d = 2; d <= n; d++) {
                    if (a == b || a == c || a == d || b == c || b == d || c == d) {
                        continue;
                    }
                    if (can_reach[1][a] && can_reach[a][b] && can_reach[b][c] &&
                        can_reach[c][d] && can_reach[d][1]) {
                        answer = max(answer, score[a] + score[b] + score[c] + score[d]);
                    }
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
