/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 09:10
 */
// 差分约束：把 x_c - x_c' <= y 变成边 c' -> c 权 y，
// 所有点距离初始为 0（等价于超级源向每个点连 0 权边）跑 SPFA 求任意一组可行解。
// 没有负环时 dis 就是可行解；出现负环说明约束自相矛盾，输出 NO。
// 模板来源：rbook 代码模板 diff-constraints（差分约束的建边、全局可行性与单源最短路）。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e3 + 5;

struct Edge {
    int to;
    ll w;
};

int n, m;
vector<Edge> g[maxn];   // g[u]：从 u 出发的边，边 u -> v 权 w 代表 x_v - x_u <= w
ll dis[maxn];           // feasible() 之后是一组可行解
int cnt[maxn];          // 当前 dis 对应的路径边数，达到 n 说明绕出了负环
bool in_queue[maxn];

// 全局可行性：所有点距离取 0 并全部入队，等价于加一个到所有点都是 0 权边的超级源点。
// 返回 false 表示存在负环、约束无解；返回 true 时 dis[1..n] 就是一组可行解。
bool feasible() {
    fill(dis, dis + n + 1, 0);
    fill(cnt, cnt + n + 1, 0);
    fill(in_queue, in_queue + n + 1, true);
    queue<int> q;
    for (int u = 1; u <= n; ++u) q.push(u);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (const Edge &e : g[u]) {
            if (dis[u] + e.w >= dis[e.to]) continue;  // 这条边给不出更紧的上界
            dis[e.to] = dis[u] + e.w;
            cnt[e.to] = cnt[u] + 1;
            if (cnt[e.to] >= n) return false;         // 更短的路用了至少 n 条边，必然有负环
            if (!in_queue[e.to]) {
                q.push(e.to);
                in_queue[e.to] = true;
            }
        }
    }
    return true;
}

void read_data() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int c, c2;
        ll y;
        cin >> c >> c2 >> y;
        // x_c - x_c' <= y  <=>  x_c <= x_c' + y，于是建边 c' -> c 权 y
        g[c2].push_back({c, y});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    read_data();

    if (!feasible()) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i) cout << dis[i] << " \n"[i == n];

    return 0;
}
