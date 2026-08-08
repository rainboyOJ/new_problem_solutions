#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250 + 5;
const long long INF = (1LL << 60);

struct NodeOrder {
    int id;
    int toll;

    bool operator < (const NodeOrder &other) const {
        if (toll != other.toll) {
            return toll < other.toll;
        }
        return id < other.id;
    }
};

int n, m, q;
int toll_fee[MAXN];
long long dist_arr[MAXN][MAXN];
long long answer[MAXN][MAXN];
NodeOrder ord[MAXN];

void solve() {
    sort(ord + 1, ord + n + 1);

    for (int k = 1; k <= n; k++) {
        int mid = ord[k].id;

        // Floyd：只允许过路费不超过 ord[k].toll 的点做中转。
        for (int i = 1; i <= n; i++) {
            if (dist_arr[i][mid] >= INF / 2) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (dist_arr[mid][j] >= INF / 2) {
                    continue;
                }
                long long nd = dist_arr[i][mid] + dist_arr[mid][j];
                if (nd < dist_arr[i][j]) {
                    dist_arr[i][j] = nd;
                }
            }
        }

        // 此时 dist_arr[i][j] 表示：
        // 中转点只允许从前 k 个点里选时，i 到 j 的最短边权和。
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist_arr[i][j] >= INF / 2) {
                    continue;
                }
                long long total_cost = dist_arr[i][j] + max(ord[k].toll, max(toll_fee[i], toll_fee[j]));
                if (total_cost < answer[i][j]) {
                    answer[i][j] = total_cost;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        cin >> toll_fee[i];
        ord[i] = {i, toll_fee[i]};
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
            answer[i][j] = INF;
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        long long len;
        cin >> u >> v >> len;

        if (len < dist_arr[u][v]) {
            dist_arr[u][v] = len;
            dist_arr[v][u] = len;
        }
    }

    solve();

    for (int i = 1; i <= q; i++) {
        int s, t;
        cin >> s >> t;
        cout << answer[s][t] << '\n';
    }

    return 0;
}
