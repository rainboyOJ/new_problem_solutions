#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

int T;
int n, m_dummy;
double x[20], y[20];
int cover[20][20];
int ans;

bool equal_double(double a, double b) {
    return fabs(a - b) < EPS;
}

void dfs(int mask, int used) {
    if (used >= ans) {
        return;
    }
    if (mask == (1 << n) - 1) {
        ans = min(ans, used);
        return;
    }

    int first = 0;
    while (mask & (1 << first)) {
        first++;
    }

    dfs(mask | (1 << first), used + 1);
    for (int j = 0; j < n; j++) {
        if (cover[first][j]) {
            dfs(mask | cover[first][j], used + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据回溯选下一条抛物线。
    cin >> T;
    while (T--) {
        cin >> n >> m_dummy;
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        for (int i = 0; i < n; i++) {
            cover[i][i] = 1 << i;
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                cover[i][j] = 0;
                if (equal_double(x[i], x[j])) {
                    continue;
                }
                double a = (y[i] / x[i] - y[j] / x[j]) / (x[i] - x[j]);
                if (a >= -EPS) {
                    continue;
                }
                double b = y[i] / x[i] - a * x[i];
                int mask = 0;
                for (int k = 0; k < n; k++) {
                    double yy = a * x[k] * x[k] + b * x[k];
                    if (equal_double(yy, y[k])) {
                        mask |= 1 << k;
                    }
                }
                cover[i][j] = mask;
            }
        }

        ans = n;
        dfs(0, 0);
        cout << ans << '\n';
    }
    return 0;
}
