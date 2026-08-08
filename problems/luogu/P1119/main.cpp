#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200 + 5;
const long long INF = (1LL << 60);

struct Query {
    int x, y, t, id;
};

int n, m;
int build_time[MAXN];
long long dist_arr[MAXN][MAXN];
Query queries[50000 + 5];
long long answer[50000 + 5];
int order_idx[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> build_time[i];
        order_idx[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < dist_arr[u][v]) {
            dist_arr[u][v] = dist_arr[v][u] = w;
        }
    }

    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> queries[i].x >> queries[i].y >> queries[i].t;
        queries[i].id = i;
    }

    sort(order_idx, order_idx + n, [&](int a, int b) {
        return build_time[a] < build_time[b];
    });

    sort(queries + 1, queries + q + 1, [&](const Query &a, const Query &b) {
        return a.t < b.t;
    });

    int ptr = 0;

    // 按时间从小到大放开村庄。
    // 每放开一个新村庄 k，就做一轮 Floyd 的“加点转移”。
    for (int i = 1; i <= q; i++) {
        while (ptr < n && build_time[order_idx[ptr]] <= queries[i].t) {
            int k = order_idx[ptr];
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (dist_arr[x][k] + dist_arr[k][y] < dist_arr[x][y]) {
                        dist_arr[x][y] = dist_arr[x][k] + dist_arr[k][y];
                    }
                }
            }
            ptr++;
        }

        int x = queries[i].x;
        int y = queries[i].y;
        int t = queries[i].t;

        if (build_time[x] > t || build_time[y] > t || dist_arr[x][y] == INF) {
            answer[queries[i].id] = -1;
        }
        else {
            answer[queries[i].id] = dist_arr[x][y];
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
