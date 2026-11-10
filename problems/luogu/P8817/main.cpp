/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:21
 * update_at: 2026-11-10 20:17
 */
// main.cpp：BFS 求可达性，每个节点保留权值前 3 候选，枚举中间两点拼出最优四元组。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2505; // n <= 2500

int n, m, k;
ll score[MAXN];             // score[i]：景点 i 的分数，可达 1e18，必须用 ll
vector<int> adj[MAXN];      // adj[u]：与 u 有直达公交线路的邻接点
bool can_reach[MAXN][MAXN]; // can_reach[x][y]：x 到 y 是否最多转车 k 次（距离 <= k+1）
vector<int> cand[MAXN];     // cand[u]：与 1 号点及 u 均在 k+1 步内可达的前 3 个高分候选景点
int dist[MAXN];             // BFS 距离数组，放全局避免爆栈

// 从 start 出发做 BFS，求出 k+1 步以内所有可达的点
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
            continue; // 最多转车 k 次即最多走 k+1 条边，不再扩展
        }

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

// 候选景点按分数降序排序
bool compare_by_score(int u, int v) {
    return score[u] > score[v];
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
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 预处理任意两点间在 k+1 步以内的可达性
    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    // 找出所有与 1 号点（家）在 k+1 步以内可达的景点
    vector<int> reach_home;
    for (int i = 2; i <= n; i++) {
        if (can_reach[1][i]) {
            reach_home.push_back(i);
        }
    }

    // 为每个景点 x 收集候选点 a：a 与 1 号点可达且 a 与 x 可达
    // 排除自身与冲突点后，可能冲突的点（c 和 d）至多 2 个，因此保留前 3 高分候选必定足够
    for (int x = 2; x <= n; x++) {
        for (int a : reach_home) {
            if (a != x && can_reach[a][x]) {
                cand[x].push_back(a);
            }
        }
        sort(cand[x].begin(), cand[x].end(), compare_by_score);
        if (cand[x].size() > 3) {
            cand[x].resize(3);
        }
    }

    // 枚举中间两点 b 和 c，分别在 cand[b] 与 cand[c] 中选 a 和 d
    ll answer = 0;
    for (int b = 2; b <= n; b++) {
        for (int c = 2; c <= n; c++) {
            if (b == c || !can_reach[b][c]) {
                continue;
            }

            for (int a : cand[b]) {
                if (a == c) {
                    continue;
                }
                for (int d : cand[c]) {
                    if (d == a || d == b) {
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
