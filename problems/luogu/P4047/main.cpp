#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXE = 1000005;

struct Edge {
    int u, v;
    long long dist2;
};

int n, k;
int x_pos[MAXN], y_pos[MAXN];
Edge edge[MAXE];
int edge_count;
int father[MAXN];

bool cmp_edge(const Edge &a, const Edge &b) {
    return a.dist2 < b.dist2;
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

long long square_dist(int i, int j) {
    long long dx = x_pos[i] - x_pos[j];
    long long dy = y_pos[i] - y_pos[j];
    return dx * dx + dy * dy;
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }
}

void build_edges() {
    edge_count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            edge_count++;
            edge[edge_count].u = i;
            edge[edge_count].v = j;
            edge[edge_count].dist2 = square_dist(i, j);
        }
    }
}

void solve() {
    build_edges();
    sort(edge + 1, edge + edge_count + 1, cmp_edge);

    for (int i = 1; i <= n; i++) {
        father[i] = i;
    }

    int components = n;
    for (int i = 1; i <= edge_count; i++) {
        int u = edge[i].u;
        int v = edge[i].v;
        if (find_root(u) == find_root(v)) {
            continue;
        }

        if (components == k) {
            double answer = sqrt((double)edge[i].dist2);
            cout << fixed << setprecision(2) << answer << '\n';
            return;
        }

        merge_set(u, v);
        components--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
