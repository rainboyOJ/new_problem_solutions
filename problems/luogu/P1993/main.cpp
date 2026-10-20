/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 14:35
 */
// 小 K 的农场：判断三类作物数量关系能否同时满足，是差分约束的可行性问题。
// 把每个农场看成变量 x_i，三类信息统一改写为 x_v <= x_u + w，建边 u -> v 权 w：
//   type 1（a 比 b 至少多 c）：x_a - x_b >= c  <=>  x_b <= x_a - c，建边 a -> b 权 -c
//   type 2（a 比 b 至多多 c）：x_a - x_b <= c  <=>  x_a <= x_b + c，建边 b -> a 权 c
//   type 3（a 与 b 一样多）：x_a = x_b，建两个方向的 0 权边
// 所有点距离取 0 并全部入队（等价于加一个 0 权超级源点）跑 SPFA，
// 没有负环说明这组约束可以被满足，输出 Yes；出现负环说明约束自相矛盾，输出 No。
// 边权有负数，所以不能用 Dijkstra。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;  // 农场数上界 n <= 5e3
const int MAXM = 5005;  // 信息数上界 m <= 5e3，每条信息最多加两条边

int n, m;
vector<pair<int, int>> graph[MAXN];  // graph[u]：若干 (终点 v, 边权 w)，代表 x_v <= x_u + w
long long dis[MAXN];                 // 当前求出的差值上界，即一组候选解
int path_len[MAXN];                  // 当前 dis 对应的路径边数，达到 n 说明绕出了环
bool in_queue[MAXN];

// 返回 false 表示存在负环、约束无解；返回 true 表示这组约束可以同时满足。
// 全局可行性检查：所有点初值取 0 并全部入队，等价于加一个到所有点都是 0 权边的超级源点。
// 初值只是假定值，解整体平移仍然合法，所以取 0 最省事。
bool feasible() {
    fill(dis, dis + n + 1, 0);
    fill(path_len, path_len + n + 1, 0);
    fill(in_queue, in_queue + n + 1, true);

    queue<int> que;
    for (int u = 1; u <= n; u++) que.push(u);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        in_queue[u] = false;

        for (const auto& e : graph[u]) {
            int v = e.first;
            long long w = e.second;
            long long candidate = dis[u] + w;
            if (candidate >= dis[v]) continue;  // 这条边给不出更紧的上界

            dis[v] = candidate;
            path_len[v] = path_len[u] + 1;
            if (path_len[v] >= n) return false;  // 更短的路用了至少 n 条边，必然有负环

            if (!in_queue[v]) {
                que.push(v);
                in_queue[v] = true;
            }
        }
    }
    return true;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            // x_a - x_b >= c  <=>  x_b <= x_a - c
            graph[a].push_back({b, -c});
        } else if (type == 2) {
            int a, b, c;
            cin >> a >> b >> c;
            // x_a - x_b <= c  <=>  x_a <= x_b + c
            graph[b].push_back({a, c});
        } else {
            int a, b;
            cin >> a >> b;
            // x_a == x_b，拆成两个方向的 0 权边
            graph[a].push_back({b, 0});
            graph[b].push_back({a, 0});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << (feasible() ? "Yes" : "No") << '\n';

    return 0;
}
