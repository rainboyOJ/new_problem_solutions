#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据 DFS 枚举进入上升点列的给定点集合，验证最优答案。

const int MAXN = 25;

struct Point {
    int x, y;
};

int n, k;
Point p[MAXN];
int best_given;

bool cmp_point(const Point &a, const Point &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

void dfs(int last, int used, int cnt) {
    best_given = max(best_given, cnt);

    for (int i = last + 1; i <= n; i++) {
        if (p[i].x < p[last].x || p[i].y < p[last].y) {
            continue;
        }

        int need = (p[i].x - p[last].x) + (p[i].y - p[last].y) - 1;
        if (used + need > k) {
            continue;
        }

        dfs(i, used + need, cnt + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p + 1, p + n + 1, cmp_point);

    best_given = 1;
    for (int i = 1; i <= n; i++) {
        dfs(i, 0, 1);
    }

    cout << best_given + k << '\n';
    return 0;
}
