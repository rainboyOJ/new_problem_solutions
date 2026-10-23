/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:40
 * update_at: 2026-10-23 13:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法完全照着题面：对每个不在 S 中的点 u，真的把 u 删掉，
// 再从 S 的第一个点做 BFS，看 S 里有没有点走不到。
// 单次询问就要 O(n(n+m))，只有 n 很小时才跑得动，所以只服务对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m, q;

vector<int> g[MAXN]; // 原图邻接表；重边直接重复存，不影响可达性判断
int in_set[MAXN];    // in_set[x]：x 是否在当前询问的占领集合 S 中
int asked[MAXN];     // 当前询问给出的点集 S，题面保证严格递增
int vis[MAXN];       // vis[x] == cur_tag 表示 x 在本轮 BFS 中已被访问
int cur_tag;         // BFS 轮次标记，避免每轮清空 vis

// 从 start 出发做 BFS，禁止经过 ban 点（ban 已被摧毁）。
void bfs(int start, int ban) {
    queue<int> que;
    cur_tag++;
    vis[start] = cur_tag;
    que.push(start);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v : g[u]) {
            if (v == ban || vis[v] == cur_tag) {
                continue;
            }
            vis[v] = cur_tag;
            que.push(v);
        }
    }
}

void solve_one_case() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= n; j++) {
            in_set[j] = 0;
        }
        for (int j = 1; j <= k; j++) {
            cin >> asked[j];
            in_set[asked[j]] = 1;
        }

        int answer = 0;
        for (int u = 1; u <= n; u++) {
            if (in_set[u]) {
                continue; // 只能摧毁没被占领的城市
            }
            bfs(asked[1], u);
            bool broken = false;
            for (int j = 1; j <= k; j++) {
                if (vis[asked[j]] != cur_tag) {
                    broken = true;
                    break;
                }
            }
            if (broken) {
                answer++;
            }
        }
        cout << answer << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        solve_one_case();
    }
    return 0;
}
