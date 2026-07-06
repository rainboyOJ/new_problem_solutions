// main.cpp：平面图最小割转对偶图最短路，再用环形区间 DP 配对颜色变化段。
#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 260000;
const int MAXEDGE = 1300000;
const long long INF = (long long)4e18;

struct Edge {
    int to;
    int next;
    int weight;
};

struct PointInfo {
    int weight;
    int position;
    int color;
};

int n, m, query_count, face_count, edge_count;
int head[MAXNODE], saved_head[MAXEDGE], saved_node[MAXEDGE], saved_count;
Edge edges[MAXEDGE];
int boundary_face[5005];
PointInfo point_info[60];
long long dist_value[MAXNODE];
bool visited_node[MAXNODE];
long long dist_between[60][60];
long long dp[120][120];
int changed_node[120];

int face_id(int x, int y) {
    return x * (m + 1) + y;
}

bool cmp_point(const PointInfo &a, const PointInfo &b) {
    return a.position < b.position;
}

void add_directed_edge(int u, int v, int w) {
    edge_count++;
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count;
}

void add_base_edge(int u, int v, int w) {
    add_directed_edge(u, v, w);
    add_directed_edge(v, u, w);
}

void add_temp_edge(int u, int v, int w) {
    saved_count++;
    saved_head[saved_count] = head[u];
    saved_node[saved_count] = u;
    add_directed_edge(u, v, w);
}

void reset_temp_edges() {
    edge_count -= saved_count;
    while (saved_count > 0) {
        head[saved_node[saved_count]] = saved_head[saved_count];
        saved_count--;
    }
}

void dijkstra(int source, int total_nodes) {
    for (int i = 0; i < total_nodes; i++) {
        dist_value[i] = INF;
        visited_node[i] = false;
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > heap;
    dist_value[source] = 0;
    heap.push(make_pair(0, source));

    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (visited_node[u]) {
            continue;
        }
        visited_node[u] = true;

        for (int e = head[u]; e != 0; e = edges[e].next) {
            int v = edges[e].to;
            long long nd = dist_value[u] + edges[e].weight;
            if (nd < dist_value[v]) {
                dist_value[v] = nd;
                heap.push(make_pair(nd, v));
            }
        }
    }
}

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

    for (int i = 1; i <= k; i++) {
        int block_node = face_count + i - 1;

        for (int p = point_info[i].position; p != point_info[i + 1].position; p = p % perimeter + 1) {
            add_temp_edge(block_node, boundary_face[p], 0);
            add_temp_edge(boundary_face[p], block_node, 0);
        }

        int next_block = (i == k) ? face_count : block_node + 1;
        int connect_weight = (i == k) ? point_info[1].weight : point_info[i + 1].weight;
        add_temp_edge(block_node, next_block, connect_weight);
        add_temp_edge(next_block, block_node, connect_weight);

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

    int total_nodes = face_count + k;
    for (int i = 0; i < change_count; i++) {
        dijkstra(boundary_blocks[i], total_nodes);
        for (int j = 0; j < change_count; j++) {
            dist_between[i][j] = dist_value[boundary_blocks[j]];
        }
    }

    for (int i = 0; i < change_count; i++) {
        changed_node[i] = i;
        changed_node[i + change_count] = i;
    }

    for (int i = 0; i < change_count * 2; i++) {
        for (int j = 0; j < change_count * 2; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 0; i + 1 < change_count * 2; i++) {
        dp[i][i + 1] = dist_between[changed_node[i]][changed_node[i + 1]];
    }

    for (int len = 4; len <= change_count; len += 2) {
        for (int l = 0; l + len - 1 < change_count * 2; l++) {
            int r = l + len - 1;
            dp[l][r] = dp[l + 1][r - 1] + dist_between[changed_node[l]][changed_node[r]];
            for (int mid = l + 1; mid <= r - 2; mid += 2) {
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r]);
            }
        }
    }

    long long answer = INF;
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

    for (int r = 1; r < n; r++) {
        for (int c = 1; c <= m; c++) {
            int w;
            cin >> w;
            add_base_edge(face_id(r, c - 1), face_id(r, c), w);
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c < m; c++) {
            int w;
            cin >> w;
            add_base_edge(face_id(r - 1, c), face_id(r, c), w);
        }
    }

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
