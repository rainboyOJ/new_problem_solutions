/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 21:03
 */
// main.cpp：平面图最小割转对偶图最短路，再用环形区间 DP 配对颜色变化段。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 260000;
const int MAXEDGE = 1300000;
const ll INF = (ll)4e18;

struct Edge {
    int to;
    int nxt; // 下一条边的编号，避开 std::next
    int weight;
};

struct PointInfo {
    int weight;
    int position;
    int color;
};

int n, m, query_count, face_count, edge_cnt;

// 对偶图链式前向星
int head[MAXNODE];
Edge edges[MAXEDGE];

// 临时边回滚机制：每次询问在对偶图上添加临时边，询问结束后回滚
int saved_head[MAXEDGE];
int saved_node[MAXEDGE];
int saved_count;

// boundary_face[p]：边界射线 p 对应的外部 face 编号
int boundary_face[5005];

// 每次询问的附加点信息
PointInfo point_info[60];

// Dijkstra 距离数组和访问标记
ll dist_value[MAXNODE];
bool visited_node[MAXNODE];

// dist_between[i][j]：第 i 个和第 j 个颜色变化点之间的最短路
ll dist_between[60][60];

// dp[i][j]：环形区间 DP，变化点 i 到 j 全部配对的最小代价
ll dp[120][120];

// changed_node[i]：环形展开后的变化点编号
int changed_node[120];

// 格点 (x,y) 对应的 face 编号（对偶图中的节点）
int face_id(int x, int y) {
    return x * (m + 1) + y;
}

// 按位置排序附加点
bool cmp_point(const PointInfo &a, const PointInfo &b) {
    return a.position < b.position;
}

// 链式前向星加一条有向边
void add_directed_edge(int u, int v, int w) {
    edge_cnt++;
    edges[edge_cnt].to = v;
    edges[edge_cnt].weight = w;
    edges[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;
}

// 加一条无向边（两条有向边）
void add_base_edge(int u, int v, int w) {
    add_directed_edge(u, v, w);
    add_directed_edge(v, u, w);
}

// 添加临时边（用于当前询问），同时记录回滚信息
void add_temp_edge(int u, int v, int w) {
    saved_count++;
    saved_head[saved_count] = head[u];
    saved_node[saved_count] = u;
    add_directed_edge(u, v, w);
}

// 回滚本次询问添加的所有临时边
void reset_temp_edges() {
    edge_cnt -= saved_count;
    while (saved_count > 0) {
        head[saved_node[saved_count]] = saved_head[saved_count];
        saved_count--;
    }
}

// Dijkstra 最短路：从 source 到所有节点的最短距离
void dijkstra(int source, int total_nodes) {
    for (int i = 0; i < total_nodes; i++) {
        dist_value[i] = INF;
        visited_node[i] = false;
    }

    // 小根堆：pair<距离, 节点>
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;
    dist_value[source] = 0;
    heap.push(make_pair(0, source));

    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (visited_node[u]) {
            continue;
        }
        visited_node[u] = true;

        for (int e = head[u]; e != 0; e = edges[e].nxt) {
            int v = edges[e].to;
            ll nd = dist_value[u] + edges[e].weight;
            if (nd < dist_value[v]) {
                dist_value[v] = nd;
                heap.push(make_pair(nd, v));
            }
        }
    }
}

// 处理一次询问
void solve_query() {
    int k;
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> point_info[i].weight >> point_info[i].position >> point_info[i].color;
    }
    sort(point_info + 1, point_info + k + 1, cmp_point);
    point_info[k + 1] = point_info[1];

    int perimeter = 2 * n + 2 * m;
    vector<int> boundary_blocks;

    // 为每段边界建立临时节点，并连接相邻边界段
    for (int i = 1; i <= k; i++) {
        int block_node = face_count + i - 1;

        // 将第 i 个附加点对应的外部区域与边界上该段的所有 face 相连
        for (int p = point_info[i].position; p != point_info[i + 1].position; p = p % perimeter + 1) {
            add_temp_edge(block_node, boundary_face[p], 0);
            add_temp_edge(boundary_face[p], block_node, 0);
        }

        // 相邻两个外部区域之间用附加边权连接
        int next_block = (i == k) ? face_count : block_node + 1;
        int connect_weight = (i == k) ? point_info[1].weight : point_info[i + 1].weight;
        add_temp_edge(block_node, next_block, connect_weight);
        add_temp_edge(next_block, block_node, connect_weight);

        // 记录颜色变化的位置
        if (point_info[i].color != point_info[i + 1].color) {
            boundary_blocks.push_back(block_node);
        }
    }

    int change_count = (int)boundary_blocks.size();
    if (change_count < 2) {
        cout << 0 << '\n';
        reset_temp_edges();
        return;
    }

    // 对每个颜色变化点跑 Dijkstra，得到两两之间的最短路
    int total_nodes = face_count + k;
    for (int i = 0; i < change_count; i++) {
        dijkstra(boundary_blocks[i], total_nodes);
        for (int j = 0; j < change_count; j++) {
            dist_between[i][j] = dist_value[boundary_blocks[j]];
        }
    }

    // 环形展开：将变化点环复制一倍，方便做环形区间 DP
    for (int i = 0; i < change_count; i++) {
        changed_node[i] = i;
        changed_node[i + change_count] = i;
    }

    for (int i = 0; i < change_count * 2; i++) {
        for (int j = 0; j < change_count * 2; j++) {
            dp[i][j] = INF;
        }
    }

    // 相邻两个变化点直接配对
    for (int i = 0; i + 1 < change_count * 2; i++) {
        dp[i][i + 1] = dist_between[changed_node[i]][changed_node[i + 1]];
    }

    // 区间 DP：枚举区间长度，计算 dp[l][r]
    for (int len = 4; len <= change_count; len += 2) {
        for (int l = 0; l + len - 1 < change_count * 2; l++) {
            int r = l + len - 1;
            dp[l][r] = dp[l + 1][r - 1] + dist_between[changed_node[l]][changed_node[r]];
            for (int mid = l + 1; mid <= r - 2; mid += 2) {
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r]);
            }
        }
    }

    // 在环形展开的所有起点中取最小值
    ll answer = INF;
    for (int start = 0; start < change_count; start++) {
        answer = min(answer, dp[start][start + change_count - 1]);
    }
    cout << answer << '\n';

    reset_temp_edges();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> query_count;
    face_count = (n + 1) * (m + 1);

    // 读入水平边（相邻行之间的边）
    for (int r = 1; r < n; r++) {
        for (int c = 1; c <= m; c++) {
            int w;
            cin >> w;
            add_base_edge(face_id(r, c - 1), face_id(r, c), w);
        }
    }

    // 读入垂直边（相邻列之间的边）
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c < m; c++) {
            int w;
            cin >> w;
            add_base_edge(face_id(r - 1, c), face_id(r, c), w);
        }
    }

    // 建立边界射线到外部 face 的映射
    for (int i = 1; i <= m; i++) {
        boundary_face[i] = face_id(0, i);
    }
    for (int i = m + 1; i <= n + m; i++) {
        boundary_face[i] = face_id(i - m, m);
    }
    for (int i = n + m + 1; i <= n + 2 * m; i++) {
        boundary_face[i] = face_id(n, n + 2 * m - i);
    }
    for (int i = n + 2 * m + 1; i <= 2 * n + 2 * m; i++) {
        boundary_face[i] = face_id(2 * n + 2 * m - i, 0);
    }

    while (query_count--) {
        solve_query();
    }

    return 0;
}
