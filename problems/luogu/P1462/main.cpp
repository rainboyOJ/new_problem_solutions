#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 100005;
const long long INF = (1LL << 62);

struct Edge {
    int to;
    int next;
    int w;
};

int n, m;
long long blood_limit;
int fee[MAXN];
int head[MAXN], edge_cnt;
Edge edges[MAXM];
long long dist_node[MAXN];

void add_edge(int u, int v, int w) {
    edge_cnt++;
    edges[edge_cnt].to = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

bool check(int limit) {
    if (fee[1] > limit || fee[n] > limit) {
        return false;
    }

    for (int i = 1; i <= n; i++) {
        dist_node[i] = INF;
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    dist_node[1] = 0;
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist_node[u]) {
            continue;
        }
        if (u == n) {
            return d <= blood_limit;
        }

        for (int e = head[u]; e != 0; e = edges[e].next) {
            int v = edges[e].to;
            if (fee[v] > limit) {
                continue;
            }
            long long nd = d + edges[e].w;
            if (nd < dist_node[v]) {
                dist_node[v] = nd;
                pq.push(make_pair(nd, v));
            }
        }
    }

    return dist_node[n] <= blood_limit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> blood_limit;
    int max_fee = 0;
    for (int i = 1; i <= n; i++) {
        cin >> fee[i];
        max_fee = max(max_fee, fee[i]);
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    if (!check(max_fee)) {
        cout << "AFK\n";
        return 0;
    }

    int left = max(fee[1], fee[n]);
    int right = max_fee;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
