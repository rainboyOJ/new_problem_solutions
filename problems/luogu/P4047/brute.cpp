#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举小数据的 k 个部落划分，用来辅助对拍。

const int MAXN = 12;

int n, k;
int x_pos[MAXN], y_pos[MAXN];
int group_id[MAXN];
double answer;

double dist_point(int i, int j) {
    double dx = x_pos[i] - x_pos[j];
    double dy = y_pos[i] - y_pos[j];
    return sqrt(dx * dx + dy * dy);
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }
}

void evaluate() {
    double nearest = 1e100;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (group_id[i] != group_id[j]) {
                nearest = min(nearest, dist_point(i, j));
            }
        }
    }
    answer = max(answer, nearest);
}

void dfs(int pos, int used_groups) {
    if (pos == n + 1) {
        if (used_groups == k) {
            evaluate();
        }
        return;
    }

    for (int g = 1; g <= used_groups; g++) {
        group_id[pos] = g;
        dfs(pos + 1, used_groups);
    }

    if (used_groups < k) {
        group_id[pos] = used_groups + 1;
        dfs(pos + 1, used_groups + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    answer = 0.0;
    group_id[1] = 1;
    dfs(2, 1);

    cout << fixed << setprecision(2) << answer << '\n';

    return 0;
}
