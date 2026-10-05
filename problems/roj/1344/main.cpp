/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:46
 * update_at: 2026-10-05 10:46
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2005;
const int MAXM = 200005; // n=2000、m≈10^5，留出正反边后约 2*10^5

// 邻接表存无向图：第 i 条边从 head[u] 串起来
int head[MAXN];
int to[MAXM];
int nxt[MAXM];
double weight[MAXM]; // 边 (x,y,z) 的"放大因子" = 100/(100-z)
int edge_cnt;

void add_edge(int u, int v, double w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

int n, m;
int start_node, end_node;

// dist[u] 表示让 u 到账 1 元时，A 至少需要出的金额倍数；初值 1
double dist_val[MAXN];

void dijkstra() {
    for (int i = 1; i <= n; i++) dist_val[i] = 1e100;
    dist_val[start_node] = 1.0;
    // 小根堆：取当前倍数最小的点继续扩展
    priority_queue<pair<double,int> > heap;
    heap.push(make_pair(-1.0, start_node));
    while (!heap.empty()) {
        double cur_factor = -heap.top().first;
        int u = heap.top().second;
        heap.pop();
        if (cur_factor > dist_val[u]) continue; // 过期堆元素，跳过
        if (u == end_node) return;              // 已经取出终点，最优倍数确定
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            double relaxed = cur_factor * weight[i]; // 再过一条边累计的倍数
            if (relaxed < dist_val[v]) {
                dist_val[v] = relaxed;
                heap.push(make_pair(-relaxed, v));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        // 手续费扣 z% 的边，对方到手 100 元要出 100/(100-z) 元，记成这个放大因子
        double factor = 100.0 / (100 - z);
        add_edge(x, y, factor);
        add_edge(y, x, factor);
    }
    cin >> start_node >> end_node;

    dijkstra();
    // B 到手 100 元，A 至少出 dist[B] * 100 元，保留 8 位小数
    cout << fixed << setprecision(8) << dist_val[end_node] * 100.0 << "\n";

    return 0;
}