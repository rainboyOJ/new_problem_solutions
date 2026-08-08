// main.cpp：BFS 预处理可达性，再枚举中间两个景点 B、C。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

int n, m, k;
long long score[MAXN];
vector<int> graph_edges[MAXN];
bool can_reach[MAXN][MAXN];
int best_node[MAXN][4]; // best_node[x] 保存能作为 x 前一个景点的高分候选

void bfs(int start) {
    static int dist[MAXN];
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

void add_candidate(int x, int node) {
    for (int i = 0; i < 4; i++) {
        if (best_node[x][i] == node) {
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (best_node[x][i] == 0 || score[node] > score[best_node[x][i]]) {
            for (int j = 3; j > i; j--) {
                best_node[x][j] = best_node[x][j - 1];
            }
            best_node[x][i] = node;
            return;
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

    for (int x = 2; x <= n; x++) {
        for (int a = 2; a <= n; a++) {
            if (a != x && can_reach[1][a] && can_reach[a][x]) {
                add_candidate(x, a);
            }
        }
    }

    long long answer = 0;
    for (int b = 2; b <= n; b++) {
        for (int c = 2; c <= n; c++) {
            if (b == c || !can_reach[b][c]) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                int a = best_node[b][i];
                if (a == 0 || a == b || a == c) {
                    continue;
                }
                for (int j = 0; j < 4; j++) {
                    int d = best_node[c][j];
                    if (d == 0 || d == a || d == b || d == c) {
                        continue;
                    }
                    answer = max(answer, score[a] + score[b] + score[c] + score[d]);
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
