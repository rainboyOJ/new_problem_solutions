/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:48
 * update_at: 2026-10-06 00:48
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 50005;

int n;
int s[MAXN];           // s[x]：x 的真约数和
vector<int> g[MAXN];   // 无向森林邻接表
int vis[MAXN];         // BFS 访问标记兼距离

// 筛法求 1..n 每个数的真约数和：d 枚举倍数
void calc_divisor_sum() {
    for (int d = 1; d <= n / 2; ++d) {
        for (int m = d * 2; m <= n; m += d) {
            s[m] += d;
        }
    }
}

// 建图：若 s[x] < x 则 x 与 s[x] 连无向边
void build_graph() {
    for (int x = 2; x <= n; ++x) {
        int y = s[x];
        if (y < x) {
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }
}

// 从 start 开始 BFS，返回 (最远点, 最远距离)，同时把访问过的点存入 reached
pair<int, int> bfs(int start, vector<int> &reached) {
    queue<int> q;
    q.push(start);
    vis[start] = 0;
    reached.push_back(start);
    int far = start;
    int maxd = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i];
            if (vis[v] != -1) continue;
            vis[v] = vis[u] + 1;
            q.push(v);
            reached.push_back(v);
            if (vis[v] > maxd) {
                maxd = vis[v];
                far = v;
            }
        }
    }
    return make_pair(far, maxd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    if (!(cin >> n)) return 0;

    calc_divisor_sum();
    build_graph();

    // 森林直径：每个连通块两次 BFS
    memset(vis, -1, sizeof(vis));
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i] != -1) continue;   // 已访问过，属于之前的连通块
        vector<int> nodes;
        pair<int, int> p1 = bfs(i, nodes);   // 第一次：找连通块一端 u，nodes 记录整块
        int u = p1.first;
        // 第二次从 u 出发，只在该连通块内 BFS
        for (int j = 0; j < (int)nodes.size(); ++j) vis[nodes[j]] = -1;
        vector<int> dummy;
        pair<int, int> p2 = bfs(u, dummy);   // 最远距离即该树直径
        ans = max(ans, p2.second);
    }

    cout << ans << "\n";
    return 0;
}
