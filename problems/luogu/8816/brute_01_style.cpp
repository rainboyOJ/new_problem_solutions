// brute_01_style.cpp：01 序列风格暴力，按排序后的点依次决定选或不选。
#include <bits/stdc++.h>
using namespace std;

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

int need_points(int last, int cur) {
    return (p[cur].x - p[last].x) + (p[cur].y - p[last].y) - 1;
}

void dfs(int dep, int last, int used_extra, int chosen_count) {
    if (dep == n + 1) {
        best_given = max(best_given, chosen_count);
        return;
    }

    // 第 dep 个给定点不选，对应 01 序列中的 0。
    dfs(dep + 1, last, used_extra, chosen_count);

    // 第 dep 个给定点选入上升点列，对应 01 序列中的 1。
    bool can_choose = false;
    int need = 0;
    if (last == 0) {
        can_choose = true;
    } else if (p[dep].x >= p[last].x && p[dep].y >= p[last].y) {
        need = need_points(last, dep);
        if (used_extra + need <= k) {
            can_choose = true;
        }
    }

    if (can_choose) {
        dfs(dep + 1, dep, used_extra + need, chosen_count + 1);
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

    best_given = 0;
    dfs(1, 0, 0, 0);

    cout << best_given + k << '\n';
    return 0;
}
