// brute_01_style.cpp：01 序列风格暴力，按排序后的点依次决定选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

struct Point {
    int x, y;
};

int n, k;
Point p[MAXN];
int choose_point[MAXN]; // choose_point[i] = 0/1，表示第 i 个给定点不选/选
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

bool check() {
    int last = 0;
    int used_extra = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_point[i] == 0) continue;
        if (last != 0) {
            if (p[i].x < p[last].x || p[i].y < p[last].y) return false;
            used_extra += need_points(last, i);
            if (used_extra > k) return false;
        }
        last = i;
    }
    return true;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_point[i] == 1) cnt++;
    }
    return cnt;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_given < value) best_given = value;
        }
        return;
    }

    // 第 dep 个给定点的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_point[dep] = i;
        dfs(dep + 1);
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
    dfs(1);

    cout << best_given + k << '\n';
    return 0;
}
