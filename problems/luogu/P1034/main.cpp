/**
 * Problem: luogu P1034 - [NOIP 2002 提高组] 矩形覆盖
 * Author: rainboy
 * Date: 2026-11-11 00:10
 * Description: 深度优先回溯搜索 + 几何互斥强剪枝
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

// 检查两个非空矩形是否完全分离（边线与顶点也不能重合/接触）
bool is_separated(const Rect &a, const Rect &b) {
    if (a.empty || b.empty) return true;
    // 两个闭矩形若相交或接触，则必定违反严格分离条件
    if (a.max_x < b.min_x || b.max_x < a.min_x || a.max_y < b.min_y || b.max_y < a.min_y) {
        return true;
    }
    return false;
}

// 检查矩形 idx 是否与所有其它矩形分离
bool check_valid(int idx) {
    for (int i = 1; i <= k; ++i) {
        if (i == idx) continue;
        if (!is_separated(rects[idx], rects[i])) {
            return false;
        }
    }
    return true;
}

void dfs(int u) {
    // 计算当前所有矩形的面积和
    int total_area = 0;
    for (int i = 1; i <= k; ++i) {
        total_area += rects[i].area();
    }

    // 最优性剪枝：当前总面积已不小于已有最优解
    if (total_area >= ans) return;

    if (u > n) {
        ans = min(ans, total_area);
        return;
    }

    bool empty_used = false;
    for (int i = 1; i <= k; ++i) {
        // 对称性剪枝：多个空矩形只需尝试第一个
        if (rects[i].empty) {
            if (empty_used) continue;
            empty_used = true;
        }

        Rect old_rect = rects[i];
        rects[i].add(pts[u].x, pts[u].y);

        // 几何合法性剪枝：新矩形不得与现有矩形相交接触
        if (check_valid(i)) {
            dfs(u + 1);
        }

        // 回溯恢复状态
        rects[i] = old_rect;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    // 预排序点坐标以加速剪枝收敛
    sort(pts + 1, pts + n + 1, [](const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    dfs(1);

    cout << ans << "\n";

    return 0;
}
