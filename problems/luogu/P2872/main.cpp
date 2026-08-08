#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXE = 1000005;

struct Edge {
    int u, v;
    double w;
};

int n, m;
long long x_pos[MAXN], y_pos[MAXN];
Edge edge[MAXE];
int edge_count;
int father[MAXN];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.w < b.w;
}

int find_root(int x) {
    if (father[x] == x) {
        return x;
    }
    father[x] = find_root(father[x]);
    return father[x];
}

bool merge_set(int x, int y) {
    int rx = find_root(x);
    int ry = find_root(y);
    if (rx == ry) {
        return false;
    }
    father[rx] = ry;
    return true;
}

double distance_between(int i, int j) {
    double dx = (double)(x_pos[i] - x_pos[j]);
    double dy = (double)(y_pos[i] - y_pos[j]);
    return sqrt(dx * dx + dy * dy);
}

void add_edge(int u, int v, double w) {
    edge_count++;
    edge[edge_count].u = u;
    edge[edge_count].v = v;
    edge[edge_count].w = w;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x_pos[i] >> y_pos[i];
        father[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        merge_set(u, v); // 已经存在的路不需要再付费。
    }
}

void build_all_edges() {
    edge_count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            add_edge(i, j, distance_between(i, j));
        }
    }
}

void solve() {
    build_all_edges();
    sort(edge + 1, edge + edge_count + 1, cmp_edge);

    double answer = 0.0;
    for (int i = 1; i <= edge_count; i++) {
        if (merge_set(edge[i].u, edge[i].v)) {
            answer += edge[i].w;
        }
    }

    cout << fixed << setprecision(2) << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
