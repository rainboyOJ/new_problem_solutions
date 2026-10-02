/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:21
 * update_at: 2026-10-01 22:21
 */
// main.cpp：先从每个点 BFS 求限制步数内的可达性，再为每个点保留高分候选，最后枚举中间两个景点。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2505;   // n <= 2500

int n, m, k;
ll score[MAXN];                // score[i]：景点 i 的分数，可达 1e18，必须用 ll
vector<int> graph_edges[MAXN]; // graph_edges[u]：与 u 有直达线路的点
bool can_reach[MAXN][MAXN];    // can_reach[x][y]：x 到 y 是否最多转车 k 次（即不超过 k+1 条边）
int best_node[MAXN][5];        // best_node[x][1..4]：能排在 x 前面的分数最高的 4 个候选景点
int dist[MAXN];                // BFS 距离数组，放全局避免大数组爆栈

// 从 start 出发做 BFS，把 k+1 条边以内可达的点都标记为 can_reach[start][y]。
void bfs(int start) {
    queue<int> q;

    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        can_reach[start][u] = true;
        if (dist[u] == k + 1) {
            continue;   // 转车 k 次最多走 k+1 条边，不能再往外扩展
        }

        int cnt = graph_edges[u].size();
        for (int i = 0; i < cnt; i++) {
            int v = graph_edges[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

// 把 node 插入 best_node[x]，按分数从高到低维护前 4 个，重复的景点不再加入。
void add_candidate(int x, int node) {
    for (int i = 1; i <= 4; i++) {
        if (best_node[x][i] == node) {
            return;
        }
    }

    for (int i = 1; i <= 4; i++) {
        if (best_node[x][i] == 0 || score[node] > score[best_node[x][i]]) {
            for (int j = 4; j > i; j--) {
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

    // best_node[x] 收的是“能排在 x 前面”的候选 a：满足 1 能到 a、a 能到 x。
    // 图是无向的，“x 后面”的候选条件形式相同，因此同一份列表可以两边复用。
    for (int x = 2; x <= n; x++) {
        for (int a = 2; a <= n; a++) {
            if (a != x && can_reach[1][a] && can_reach[a][x]) {
                add_candidate(x, a);
            }
        }
    }

    ll answer = 0;
    for (int b = 2; b <= n; b++) {
        for (int c = 2; c <= n; c++) {
            if (b == c || !can_reach[b][c]) {
                continue;
            }

            // b 的候选取 A、c 的候选取 D，凑出四个互不相同的景点。
            // 每份候选最多被 3 个点排除，所以保留前 4 个一定能取到最优。
            for (int i = 1; i <= 4; i++) {
                int a = best_node[b][i];
                if (a == 0 || a == b || a == c) {
                    continue;
                }
                for (int j = 1; j <= 4; j++) {
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
