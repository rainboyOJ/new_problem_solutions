#include <bits/stdc++.h>
using namespace std;

const double INF = 1e100;

int n;
double limit_d;
double x[25], y_[25];
double dis_mat[25][25];
int used[25];
double ans;

double dist(int i, int j) {
    double dx = x[i] - x[j];
    double dy = y_[i] - y_[j];
    return sqrt(dx * dx + dy * dy);
}

void dfs_perm(int last, int cnt, double cur) {
    if (cur >= ans) {
        return;
    }
    if (cnt == n) {
        ans = min(ans, cur + dis_mat[last][1]);
        return;
    }

    for (int i = 2; i <= n; i++) {
        if (used[i] || dis_mat[last][i] >= INF / 2) {
            continue;
        }
        used[i] = 1;
        dfs_perm(i, cnt + 1, cur + dis_mat[last][i]);
        used[i] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据先 Floyd，再直接枚举访问顺序。
    cin >> n >> limit_d;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y_[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            double d = dist(i, j);
            if (d <= limit_d) {
                dis_mat[i][j] = d;
            } else {
                dis_mat[i][j] = INF;
            }
        }
        dis_mat[i][i] = 0;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis_mat[i][k] + dis_mat[k][j] < dis_mat[i][j]) {
                    dis_mat[i][j] = dis_mat[i][k] + dis_mat[k][j];
                }
            }
        }
    }

    memset(used, 0, sizeof(used));
    ans = INF;
    dfs_perm(1, 1, 0.0);

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
    return 0;
}
