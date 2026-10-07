/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:13
 * update_at: 2026-10-06 17:13
 */
#include <iostream>
#include <deque>
using namespace std;

const int MAXN = 1005;   // 城市数上限
const int MAXM = 20005;  // 无向边两倍存储
const int MAXF = 110;    // 油量维度上限（C ≤ 100，再加 1）
const int MAXW = 100;    // 单条权值上限（油价 ≤ 100）
const int INF = 0x3f3f3f3f;

typedef long long ll;

int n, m, q;
int price[MAXN]; // price[u]：城市 u 的单位油价

// 链式前向星存储无向图
int head[MAXN], to[MAXM], wt[MAXM], nxt[MAXM], edge_cnt;

// 分层图最短路状态：(u, f) 表示在城市 u、油箱剩 f 升；dist[u][f] 为到达该状态的最少油钱
int dist[MAXN][MAXF];

// 当前询问的参数
int cap, start_city, target_city;

// 环形桶队列：权值只有 0 或 price ≤ 100，用 101 个桶按花费对 101 取模
deque<int> bucket[MAXW + 1];

void add_edge(int u, int v, int d) {
    edge_cnt++;
    to[edge_cnt] = v;
    wt[edge_cnt] = d;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 把城市与剩余油量编码成一个整数，方便放进桶里。
int encode_state(int u, int f) {
    return u * (cap + 1) + f;
}

// 在状态图上跑 Dial 桶队列最短路：加油 +price[u]，开车 +0。
// 返回最少油钱；不可达返回 INF。
int dial_shortest() {
    for (int u = 0; u < n; u++) {
        for (int f = 0; f <= cap; f++) {
            dist[u][f] = INF;
        }
    }
    for (int i = 0; i <= MAXW; i++) {
        bucket[i].clear();
    }

    int mod = MAXW + 1;
    dist[start_city][0] = 0;
    bucket[0].push_back(encode_state(start_city, 0));
    int pending = 1; // 桶里还没处理的状态数量
    int cost = 0;    // 当前正在处理的花费，单调不减

    while (pending > 0) {
        // 同一花费层内开车不花钱，产生的状态留在本桶继续扩展
        while (!bucket[cost % mod].empty()) {
            int id = bucket[cost % mod].front();
            bucket[cost % mod].pop_front();
            pending--;
            int u = id / (cap + 1);
            int f = id % (cap + 1);
            if (dist[u][f] != cost) {
                continue; // 入桶后又出现过更便宜的记录，此条已过期
            }
            if (u == target_city) {
                return cost; // 花费单调不降，首次取出终点即最优
            }
            // 加油 1 升：花费增加 price[u]，进入更贵的桶
            if (f < cap && cost + price[u] < dist[u][f + 1]) {
                dist[u][f + 1] = cost + price[u];
                bucket[(cost + price[u]) % mod].push_back(encode_state(u, f + 1));
                pending++;
            }
            // 开车去相邻城市：油够才走，油量减少、花费不变
            for (int i = head[u]; i != 0; i = nxt[i]) {
                int v = to[i];
                int nf = f - wt[i];
                if (nf >= 0 && cost < dist[v][nf]) {
                    dist[v][nf] = cost;
                    bucket[cost % mod].push_back(encode_state(v, nf));
                    pending++;
                }
            }
        }
        cost++;
    }
    return INF;
}

void solve() {
    cin >> n >> m;
    for (int u = 0; u < n; u++) {
        cin >> price[u];
    }
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        add_edge(u, v, d);
        add_edge(v, u, d); // 无向图加两条反向边
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> cap >> start_city >> target_city;
        int ans = dial_shortest();
        if (ans == INF) {
            cout << "impossible" << '\n';
        } else {
            cout << ans << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
