/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-20 05:08
 * update_at: 2026-10-18 20:48
 */
// main.cpp：不显式建分层图，直接把「用了几次免费机会」当成 dis 的第二维，
// 在 Dijkstra 的松弛里同时做两种转移（付费留在本层 / 免费降到下一层）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5; // 城市数上限
const int MAXK = 10 + 5;    // k 上限 10
const ll INF = (1LL << 60);

// 一条有向边：终点 v 和花费 w。
struct Edge {
    int v;
    int w;
};

int n, m, k;
int s, t;
vector<Edge> g[MAXN]; // g[u]：城市 u 的所有出边
// dist_arr[city][used]：从起点到达 city、恰好使用 used 次免费机会的最小花费
ll dist_arr[MAXN][MAXK];
bool done[MAXN][MAXK]; // done[city][used]：该状态是否已经定稿

struct HeapNode {
    ll dist;
    int city;
    int used;

    // 小根堆：花费小的状态先出队。
    bool operator<(const HeapNode &other) const {
        return dist > other.dist;
    }
};

void add_edge(int u, int v, int len) {
    g[u].push_back({v, len});
}

void read_input() {
    cin >> n >> m >> k;
    cin >> s >> t;
    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        add_edge(u, v, len);
        add_edge(v, u, len);
    }
}

void dijkstra() {
    for (int city = 0; city < n; city++) {
        for (int used = 0; used <= k; used++) {
            dist_arr[city][used] = INF;
            done[city][used] = false;
        }
    }

    priority_queue<HeapNode> pq;
    dist_arr[s][0] = 0; // 起点一次免费机会都还没用
    pq.push({0, s, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.city;
        int used = cur.used;
        if (done[u][used]) {
            continue; // 过期条目，或该状态已经用它自己的最优值扩展过
        }
        done[u][used] = true;

        for (const auto &e : g[u]) {
            int v = e.v;

            // 转移一：这次不免费，付费留在本层。
            ll paid = dist_arr[u][used] + e.w;
            if (paid < dist_arr[v][used]) {
                dist_arr[v][used] = paid;
                pq.push({paid, v, used});
            }

            // 转移二：这次免费用掉一张券，代价不变但层数加一。
            if (used < k && dist_arr[u][used] < dist_arr[v][used + 1]) {
                dist_arr[v][used + 1] = dist_arr[u][used];
                pq.push({dist_arr[u][used], v, used + 1});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    dijkstra();

    // 题目是「最多 k 次」：只取 dist_arr[t][k] 会错，
    // 最优路径可能只用了不到 k 次机会，甚至第 k 层根本不可达。
    ll answer = INF;
    for (int used = 0; used <= k; used++) {
        if (dist_arr[t][used] < answer) {
            answer = dist_arr[t][used];
        }
    }

    cout << answer << '\n';

    return 0;
}
