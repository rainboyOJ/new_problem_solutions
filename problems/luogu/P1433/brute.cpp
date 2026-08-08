#include <bits/stdc++.h>
using namespace std;

const double INF = 1e100;

int n;
double x[20], y_[20];
int used[20];
double ans;

double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

void dfs(int cnt, double cx, double cy, double cur) {
    if (cur >= ans) {
        return;
    }
    if (cnt == n) {
        ans = min(ans, cur);
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = 1;
        dfs(cnt + 1, x[i], y_[i], cur + dist(cx, cy, x[i], y_[i]));
        used[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：直接枚举吃奶酪的顺序。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y_[i];
    }

    memset(used, 0, sizeof(used));
    ans = INF;
    dfs(0, 0, 0, 0.0);

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
    return 0;
}
