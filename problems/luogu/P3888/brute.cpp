#include <bits/stdc++.h>
using namespace std;

long long w[10][10];
int n, m;
long long best_cost;
int best_cnt;

bool better(long long cost, int cnt) {
    if (cost != best_cost) {
        return cost < best_cost;
    }
    return cnt < best_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：直接枚举哪些格子建油库，检查是否覆盖整张图。
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> w[i][j];
        }
    }

    int tot = n * m;
    best_cost = (1LL << 60);
    best_cnt = tot + 1;

    for (int mask = 0; mask < (1 << tot); mask++) {
        vector<vector<int> > cover(n, vector<int>(m, 0));
        long long cost = 0;
        int cnt = 0;
        for (int id = 0; id < tot; id++) {
            if (!(mask & (1 << id))) {
                continue;
            }
            int x = id / m;
            int y = id % m;
            cost += w[x][y];
            cnt++;
            int dx[5] = {0, 1, -1, 0, 0};
            int dy[5] = {0, 0, 0, 1, -1};
            for (int k = 0; k < 5; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                    cover[nx][ny] = 1;
                }
            }
        }
        bool ok = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!cover[i][j]) {
                    ok = false;
                }
            }
        }
        if (ok && better(cost, cnt)) {
            best_cost = cost;
            best_cnt = cnt;
        }
    }

    cout << best_cnt << ' ' << best_cost << '\n';
    return 0;
}
