/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:44
 * update_at: 2026-10-06 10:44
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 205;
const ll INF = (1LL << 60);

ll n, m;
ll cap[MAXM][MAXM]; // 残量网络邻接矩阵：cap[u][v] 为 u 到 v 剩余的容量
int level[MAXM];    // 层次图：每个点在残量网络上的最短边数层次，-1 表示未访问
int cur[MAXM];      // 当前弧：每个点下一轮要从哪个邻接点开始尝试

// 在残量网络上从源点 s 分层，返回汇点 t 是否仍可达（即还有增广路）。
bool bfs(int s, int t) {
    for (int i = 1; i <= m; i++) {
        level[i] = -1;
    }
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= m; v++) {
            // 该排水沟还有残量且对端尚未分层
            if (cap[u][v] > 0 && level[v] < 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] >= 0;
}

// 沿层次图从 u 向汇点 t 推送不超过 f 的流，返回实际推送量。
ll dfs(int u, int t, ll f) {
    if (u == t) {
        return f;
    }
    for (; cur[u] <= m; cur[u]++) {
        int v = cur[u];
        // 只走层次恰好 +1 的残量边
        if (cap[u][v] > 0 && level[v] == level[u] + 1) {
            ll pushed = dfs(v, t, min(f, cap[u][v]));
            if (pushed > 0) {
                cap[u][v] -= pushed; // 正向边扣残量
                cap[v][u] += pushed; // 反向边留出可回退的容量
                return pushed;
            }
        }
    }
    return 0;
}

void solve() {
    ll flow = 0;
    while (bfs(1, m)) { // 水潭 1 为源，小溪 m 为汇
        for (int i = 1; i <= m; i++) {
            cur[i] = 1;
        }
        ll pushed = dfs(1, m, INF);
        while (pushed > 0) {
            flow += pushed;
            pushed = dfs(1, m, INF);
        }
    }
    cout << flow << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        int s, e;
        ll c;
        cin >> s >> e >> c;
        // 平行边直接累加；自环不贡献流量，跳过
        if (s != e) {
            cap[s][e] += c;
        }
    }

    solve();

    return 0;
}
