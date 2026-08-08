#include <bits/stdc++.h>
using namespace std;

const int MAXP = 505;
const int MAXE = 130000;

struct Edge {
    int u, v;
    double w;
};

int s, p;
int x_pos[MAXP], y_pos[MAXP];
Edge edge[MAXE];
int edge_count;
int father[MAXP];

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
    double dx = x_pos[i] - x_pos[j];
    double dy = y_pos[i] - y_pos[j];
    return sqrt(dx * dx + dy * dy);
}

void read_input() {
    cin >> s >> p;
    for (int i = 1; i <= p; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }
}

void build_edges() {
    edge_count = 0;
    for (int i = 1; i <= p; i++) {
        for (int j = i + 1; j <= p; j++) {
            edge_count++;
            edge[edge_count].u = i;
            edge[edge_count].v = j;
            edge[edge_count].w = distance_between(i, j);
        }
    }
}

void solve() {
    build_edges();
    sort(edge + 1, edge + edge_count + 1, cmp_edge);

    for (int i = 1; i <= p; i++) {
        father[i] = i;
    }

    int components = p;
    double answer = 0.0;
    for (int i = 1; i <= edge_count && components > s; i++) {
        if (merge_set(edge[i].u, edge[i].v)) {
            answer = edge[i].w;
            components--;
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
