// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int T;
int n, m;
long long L, V;
long long d[MAXN], v[MAXN], a[MAXN], p[MAXN];
vector<int> cover[MAXN];

bool is_speeding(long long id, long long pos) {
    long long value = v[id] * v[id] + 2LL * a[id] * (pos - d[id]);
    return value > V * V;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m >> L >> V;
        for (int i = 1; i <= n; i++) {
            cin >> d[i] >> v[i] >> a[i];
            cover[i].clear();
        }
        for (int j = 1; j <= m; j++) {
            cin >> p[j];
        }

        int speeding_cars = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j] < d[i]) {
                    continue;
                }
                if (is_speeding(i, p[j])) {
                    cover[i].push_back(j);
                }
            }
            if (!cover[i].empty()) {
                speeding_cars++;
            }
        }

        int best_keep = m;
        int total = 1 << m;

        for (int mask = 0; mask < total; mask++) {
            bool ok = true;

            for (int i = 1; i <= n && ok; i++) {
                if (cover[i].empty()) {
                    continue;
                }

                bool caught = false;
                for (int k = 0; k < (int)cover[i].size(); k++) {
                    int sensor = cover[i][k] - 1;
                    if (mask & (1 << sensor)) {
                        caught = true;
                        break;
                    }
                }
                if (!caught) {
                    ok = false;
                }
            }

            if (ok) {
                int keep = 0;
                for (int j = 0; j < m; j++) {
                    if (mask & (1 << j)) {
                        keep++;
                    }
                }
                best_keep = min(best_keep, keep);
            }
        }

        cout << speeding_cars << ' ' << m - best_keep << '\n';
    }

    return 0;
}
