/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:11
 * update_at: 2026-10-05 05:12
 */
// main.cpp：道路连通块缩点 + 拓扑序 + 逐块 Dijkstra（USACO 2011 Jan Gold 道路和航线）。
// 负权航线被限制在块间、由拓扑序消化；块内只有非负道路，Dijkstra 安全。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> Node; // 堆元素：first 为距离，second 为城镇编号

const int MAXT = 25005; // 城镇数上限
const int MAXR = 50005; // 道路数上限
const int MAXP = 50005; // 航线数上限

const ll INF = 1000000000000000000LL; // 不可达哨兵，远大于任何真实最短路绝对值

int T, R, P, S; // T<=2.5e4，R,P<=5e4，用 int 可直接当下标与循环上界

// 道路：无向非负权。链式前向星存双向边，故开 2*MAXR。
int head_road[MAXT], to_road[2 * MAXR], nxt_road[2 * MAXR];
int w_road[2 * MAXR]; // 道路边权 0..10^4，用 int 省内存
int road_cnt;

// 航线：有向可负权。
int head_plane[MAXT], to_plane[MAXP], nxt_plane[MAXP];
int w_plane[MAXP]; // 航线边权 -10^4..10^4，用 int 省内存
int plane_cnt;

int comp[MAXT];            // comp[u] = 城镇 u 所属道路连通块编号（从 0 开始）
int comp_cnt;              // 道路连通块总数
vector<int> members[MAXT]; // members[c] = 第 c 个连通块内的城镇列表
vector<int> dag[MAXT];     // dag[c] = 超级点 c 经航线指向的超级点
int indeg[MAXT];           // 超级点入度，用于 Kahn 拓扑排序
ll dist[MAXT];             // dist[u] = 起点 S 到城镇 u 的最短路，INF 表示不可达

// 加一条无向道路（拆成两条有向边）。
void add_road(int u, int v, int w) {
    road_cnt++;
    to_road[road_cnt] = v;
    w_road[road_cnt] = w;
    nxt_road[road_cnt] = head_road[u];
    head_road[u] = road_cnt;
}

// 加一条单向航线。
void add_plane(int u, int v, int w) {
    plane_cnt++;
    to_plane[plane_cnt] = v;
    w_plane[plane_cnt] = w;
    nxt_plane[plane_cnt] = head_plane[u];
    head_plane[u] = plane_cnt;
}

void read_input() {
    cin >> T >> R >> P >> S;
    for (int i = 1; i <= R; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_road(a, b, c);
        add_road(b, a, c);
    }
    for (int i = 1; i <= P; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add_plane(a, b, c);
    }
}

// 只走道路做 BFS，把每个城镇归入一个道路连通块。
void build_components() {
    int que[MAXT];
    for (int s = 1; s <= T; s++) {
        if (comp[s] != -1) continue;
        int c = comp_cnt;
        comp_cnt++;
        comp[s] = c;
        members[c].push_back(s);
        int head = 0, tail = 0;
        que[tail] = s;
        tail++;
        while (head < tail) {
            int u = que[head];
            head++;
            for (int i = head_road[u]; i != 0; i = nxt_road[i]) {
                int v = to_road[i];
                if (comp[v] == -1) {
                    comp[v] = c;
                    members[c].push_back(v);
                    que[tail] = v;
                    tail++;
                }
            }
        }
    }
}

// 把航线投影到超级点上，得到块间 DAG 与各超级点入度。
void build_dag() {
    for (int a = 1; a <= T; a++) {
        for (int i = head_plane[a]; i != 0; i = nxt_plane[i]) {
            int b = to_plane[i];
            if (comp[a] == comp[b]) continue; // 题面保证不存在块内航线，这里防御性跳过
            dag[comp[a]].push_back(comp[b]);
            indeg[comp[b]]++;
        }
    }
}

// 按拓扑序逐块 Dijkstra：块内负权已由块外航线送入初值，块内只剩非负道路。
void solve() {
    dist[S] = 0;
    priority_queue<Node, vector<Node>, greater<Node> > heap;
    queue<int> topo;
    for (int c = 0; c < comp_cnt; c++) {
        if (indeg[c] == 0) topo.push(c);
    }
    while (!topo.empty()) {
        int c = topo.front();
        topo.pop();

        // 块内所有已定值的城镇作为多源起点，只遍历本块成员，避免扫描全部城镇。
        for (size_t k = 0; k < members[c].size(); k++) {
            int u = members[c][k];
            if (dist[u] < INF) heap.push(Node(dist[u], u));
        }

        while (!heap.empty()) {
            Node cur = heap.top();
            heap.pop();
            ll d = cur.first;
            int u = cur.second;
            if (d > dist[u]) continue;

            // 跨块航线：只更新目标块的距离，绝不入本块的堆（目标块的点尚未定值）。
            for (int i = head_plane[u]; i != 0; i = nxt_plane[i]) {
                int v = to_plane[i];
                ll nd = d + w_plane[i];
                if (nd < dist[v]) dist[v] = nd;
            }
            // 道路权非负，Dijkstra 安全。
            for (int i = head_road[u]; i != 0; i = nxt_road[i]) {
                int v = to_road[i];
                ll nd = d + w_road[i];
                if (nd < dist[v]) {
                    dist[v] = nd;
                    heap.push(Node(nd, v));
                }
            }
        }

        // 当前块处理完毕，给它在 DAG 中的后继块减少入度。
        for (size_t k = 0; k < dag[c].size(); k++) {
            int y = dag[c][k];
            indeg[y]--;
            if (indeg[y] == 0) topo.push(y);
        }
    }
}

void write_output() {
    for (int i = 1; i <= T; i++) {
        if (dist[i] == INF) cout << "NO PATH" << '\n';
        else cout << dist[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    // 只初始化实际用到的 1..T，其余下标永远不会被访问。
    for (int i = 1; i <= T; i++) {
        comp[i] = -1;
        dist[i] = INF;
    }

    build_components();
    build_dag();
    solve();
    write_output();

    return 0;
}
