/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:59
 * update_at: 2026-10-06 09:59
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int NODE_COUNT = 52;   // a..z 与 A..Z 共 52 个顶点
const int COW_FIRST = 26;    // 'A' 的编号
const int BARN = 51;         // 'Z' 的编号
const ll INF = (1LL << 60);

// 邻接表：每个顶点保存 (邻居, 权重的最小值)
vector< pair<int, int> > adj[NODE_COUNT];
ll dist[NODE_COUNT];

// 把单字母标记映射成编号：a..z -> 0..25，A..Z -> 26..51
int node_id(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

// 从 src 出发的 Dijkstra
void dijkstra(int src) {
    for (int i = 0; i < NODE_COUNT; i++) dist[i] = INF;
    dist[src] = 0;
    priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > q;
    q.push(make_pair(0, src));
    while (!q.empty()) {
        pair<ll, int> cur = q.top(); q.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d > dist[u]) continue; // 过期条目
        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int p;
    if (!(cin >> p)) return 0;
    // 先用临时数组去重边（保留最小权重）
    int tmp[NODE_COUNT][NODE_COUNT];
    for (int i = 0; i < NODE_COUNT; i++)
        for (int j = 0; j < NODE_COUNT; j++)
            tmp[i][j] = -1;

    for (int i = 0; i < p; i++) {
        char cu, cv;
        int w;
        cin >> cu >> cv >> w;
        int u = node_id(cu);
        int v = node_id(cv);
        if (tmp[u][v] == -1 || w < tmp[u][v]) {
            tmp[u][v] = w;
            tmp[v][u] = w;
        }
    }

    for (int u = 0; u < NODE_COUNT; u++) {
        for (int v = 0; v < NODE_COUNT; v++) {
            if (tmp[u][v] != -1) {
                adj[u].push_back(make_pair(v, tmp[u][v]));
            }
        }
    }

    dijkstra(BARN); // 无向图，从谷仓出发一次即可

    int best = COW_FIRST;
    for (int v = COW_FIRST + 1; v < BARN; v++) { // 只在 A..Y 里找
        if (dist[v] < dist[best]) best = v;
    }

    cout << (char)(best + 'A' - 26) << ' ' << dist[best] << '\n';
    return 0;
}
