/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:11
 * update_at: 2026-10-05 00:11
 */

// 1382 最短路：边权全为正的无向图单源最短路，堆优化 Dijkstra。
// N 第一次出堆时它的候选距离已不可能再变小，直接得到答案。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 500005;

typedef long long ll;

int n, m;
int head[MAXN], nxt[MAXM * 2], to[MAXM * 2], edge_cnt; // 链式前向星，无向边存两条
ll weight[MAXM * 2]; // 边权用 ll，最短路累加不会溢出
ll dist_[MAXN]; // dist_[u] 表示当前 1 到 u 的候选最短距离
bool done[MAXN]; // done[u] 为 true 表示 u 已定型（第一次出堆）

priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > heap; // 小根堆：(候选距离, 点)

// 加一条 u -> v、长 w 的边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 堆优化 Dijkstra：按距离从小到大定型每个点，返回 1 到 n 的最短距离。
// 重边、自环不用特判：松弛条件是严格小于，较大的重边自然落败，正权自环永远松弛失败。
ll dijkstra() {
    const ll INF = 1e18;
    for (int i = 1; i <= n; i++) {
        dist_[i] = INF;
        done[i] = false;
    }
    dist_[1] = 0;
    while (!heap.empty()) heap.pop(); // 清空全局堆
    heap.push(make_pair(0LL, 1));

    while (!heap.empty()) {
        int u = heap.top().second;
        ll d = heap.top().first;
        heap.pop();
        if (done[u]) continue; // 过期条目：u 已被更小的距离定型过，跳过
        done[u] = true;
        if (u == n) return d; // n 第一次出堆，答案已确定，提前返回
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            ll nd = d + weight[i];
            if (nd < dist_[v]) { // 松弛成功才压堆，堆中可能同点多条目，靠 done 惰性删除
                dist_[v] = nd;
                heap.push(make_pair(nd, v));
            }
        }
    }
    return dist_[n]; // 题面保证 1 与 n 连通，正常运行到不了这里
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edge_cnt = 0;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_edge(a, b, c); // 无向边两端各存一条
        add_edge(b, a, c);
    }

    cout << dijkstra() << "\n";

    return 0;
}
