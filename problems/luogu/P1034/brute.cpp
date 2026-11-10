/**
 * Problem: luogu P1034 - [NOIP 2002 提高组] 矩形覆盖 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-11 00:10
 * Description: 基础 DFS 搜索基准实现
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Point {
    int x, y;
};

struct Rect {
    int min_x, max_x;
    int min_y, max_y;
    bool empty;

    Rect() : min_x(INF), max_x(-INF), min_y(INF), max_y(-INF), empty(true) {}

    void add(int x, int y) {
        if (empty) {
            min_x = max_x = x;
            min_y = max_y = y;
            empty = false;
        } else {
            min_x = min(min_x, x);
            max_x = max(max_x, x);
            min_y = min(min_y, y);
            max_y = max(max_y, y);
        }
    }

    int area() const {
        if (empty) return 0;
        return (max_x - min_x) * (max_y - min_y);
    }
};

int n, k;
Point pts[55];
Rect rects[5];
int ans = INF;

bool is_separated(const Rect &a, const Rect &b) {
    if (a.empty || b.empty) return true;
    if (a.max_x < b.min_x || b.max_x < a.min_x || a.max_y < b.min_y || b.max_y < a.min_y) {
        return true;
    }
    return false;
}

bool check_all_separated() {
    for (int i = 1; i <= k; ++i) {
        for (int j = i + 1; j <= k; ++j) {
            if (!is_separated(rects[i], rects[j])) {
                return false;
            }
        }
    }
    return true;
}

void dfs_brute(int u) {
    int total_area = 0;
    for (int i = 1; i <= k; ++i) {
        total_area += rects[i].area();
    }
    if (total_area >= ans) return;

    if (u > n) {
        if (check_all_separated()) {
            ans = min(ans, total_area);
        }
        return;
    }

    bool used_empty = false;
    for (int i = 1; i <= k; ++i) {
        if (rects[i].empty) {
            if (used_empty) continue;
            used_empty = true;
        }

        Rect old_r = rects[i];
        rects[i].add(pts[u].x, pts[u].y);

        dfs_brute(u + 1);

        rects[i] = old_r;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    dfs_brute(1);

    cout << ans << "\n";

    return 0;
}
