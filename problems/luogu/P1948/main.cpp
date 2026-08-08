#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXP = 10005;
const int INF = 1000000000;

int n, p, k;
int head[MAXN], to[MAXP * 2], weight_edge[MAXP * 2], nxt[MAXP * 2], edge_cnt;
int dist_count[MAXN];

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> p >> k;
    for (int i = 1; i <= p; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        add_edge(a, b, l);
        add_edge(b, a, l);
    }
}

bool check(int limit) {
    for (int i = 1; i <= n; i++) {
        dist_count[i] = INF;
    }

    deque<int> que;
    dist_count[1] = 0;
    que.push_back(1);

    while (!que.empty()) {
        int u = que.front();
        que.pop_front();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int cost = (weight_edge[i] > limit) ? 1 : 0;
            if (dist_count[u] + cost < dist_count[v]) {
                dist_count[v] = dist_count[u] + cost;
                if (cost == 0) {
                    que.push_front(v);
                } else {
                    que.push_back(v);
                }
            }
        }
    }

    return dist_count[n] <= k;
}

void solve() {
    if (!check(INF)) {
        cout << -1 << '\n';
        return;
    }

    int left = 0;
    int right = 1000000;
    int answer = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
