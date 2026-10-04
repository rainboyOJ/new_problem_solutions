/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:11
 * update_at: 2026-10-05 00:11
 */
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 2505;  // 城镇数上限 2500
const int MAXM = 20005; // 每条道路双向各存一条有向边，2 * 6200 条
const ll INF = (1LL << 60); // 比任何可行路径都大的哨兵

ll T;         // 城镇数
ll C;         // 道路数
int Ts;       // 起点城镇编号，值域 ≤ 2500，与数组下标一致用 int
int Te;       // 终点城镇编号
int head[MAXN];   // head[u] 表示从 u 出发的第一条边编号，链式前向星
int to[MAXM];     // 边指向的城镇
int weight[MAXM]; // 边的通过费用
int nxt[MAXM];    // 同一起点下的下一条边编号
int edge_cnt;     // 已加入的有向边条数
ll dist[MAXN];    // dist[v] 表示当前 Ts 到 v 的最小费用上界

// 加入一条 u -> v、费用为 w 的有向边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> T >> C >> Ts >> Te;
    for (ll i = 1; i <= C; i++) {
        int rs; // 道路起点，值域 ≤ 2500
        int re; // 道路终点
        int ci; // 通过费用
        cin >> rs >> re >> ci;
        // 道路双向连通，两个方向各加一条边；重边也各存一次，松弛时取小者即可
        add_edge(rs, re, ci);
        add_edge(re, rs, ci);
    }
}

// 非负权无向图上的单源最短路：堆优化 Dijkstra，惰性删除过期堆记录。
ll dijkstra() {
    for (int i = 1; i <= T; i++) {
        dist[i] = INF;
    }
    dist[Ts] = 0;

    // 小根堆，存 (当前费用, 城镇)，按费用从小到大弹出
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    pq.push(make_pair(dist[Ts], Ts));

    while (!pq.empty()) {
        pair<ll, int> top = pq.top();
        pq.pop();
        ll d = top.first;
        int u = top.second;

        if (d != dist[u]) {
            continue; // 过期记录：u 已被更短的路径更新过
        }
        if (u == Te) {
            return d; // 非负权下第一次弹出终点，d 就是最终答案
        }

        // 定型 u，用它的每条出边松弛邻居
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            ll nd = d + weight[i];
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }

    return dist[Te];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << dijkstra() << "\n";

    return 0;
}
