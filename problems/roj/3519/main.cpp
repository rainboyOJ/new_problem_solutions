/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 10:00
 * update_at: 2026-10-09 16:10
 */
// 3519 [NOIP2002-提高] 矩形覆盖
// k <= 4，直接 DFS 枚举每个点归到哪个矩形：
//   1. 合法性剪枝：扩张后若与别的矩形相交或只是边线/顶点相碰，一律回溯；
//   2. 最优性剪枝：当前已分配的面积和 >= 已有答案就剪掉（面积只会越来越大）；
//   3. 对称性剪枝：把一个点放进「第 i 个空矩形」与放进「下一个空矩形」等价，
//      所以试完第一个空矩形后直接 break。
// 点先按 x 排序，让空间上相近的点先归到一起，尽早得到一个较小的答案。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 55;
const int MAXK = 5;
const int INF = 1000000000;

struct Point {
    int x, y;
};
Point p[MAXN]; // 点集，读入后按 x 升序排列

// 一个矩形就是它的外接盒；valid = false 表示这个矩形还没用上
struct Rect {
    int min_x, max_x, min_y, max_y;
    bool valid;
};
Rect r[MAXK];

int n, k;
ll ans;

// 矩形面积；覆盖一个点或一条线段的矩形面积为 0
ll rect_area(const Rect& a) {
    if (!a.valid) return 0;
    ll w = a.max_x - a.min_x;
    ll h = a.max_y - a.min_y;
    return w * h;
}

// 把点 (x, y) 并入矩形 a
void expand(Rect& a, int x, int y) {
    if (!a.valid) {
        a.min_x = a.max_x = x;
        a.min_y = a.max_y = y;
        a.valid = true;
        return;
    }
    if (x < a.min_x) a.min_x = x;
    if (x > a.max_x) a.max_x = x;
    if (y < a.min_y) a.min_y = y;
    if (y > a.max_y) a.max_y = y;
}

// a、b 是否相交或接触；「完全分开」要求边线与顶点都不重合，故用严格小于
bool touched(const Rect& a, const Rect& b) {
    if (!a.valid || !b.valid) return false; // 未使用的矩形不参与判定
    if (a.max_x < b.min_x) return false;
    if (b.max_x < a.min_x) return false;
    if (a.max_y < b.min_y) return false;
    if (b.max_y < a.min_y) return false;
    return true;
}

bool cmp_point(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

void dfs(int u) {
    ll cur = 0;
    for (int i = 0; i < k; i++) cur += rect_area(r[i]);
    if (cur >= ans) return; // 最优性剪枝

    if (u == n) {
        ans = cur;
        return;
    }

    for (int i = 0; i < k; i++) {
        bool empty_slot = !r[i].valid; // 该矩形原先为空，用于对称性剪枝
        Rect backup = r[i];
        expand(r[i], p[u].x, p[u].y);

        bool ok = true;
        for (int j = 0; j < k; j++) {
            if (i == j) continue;
            if (touched(r[i], r[j])) {
                ok = false;
                break;
            }
        }
        if (ok) dfs(u + 1);

        r[i] = backup;         // 恢复现场
        if (empty_slot) break; // 空矩形彼此等价，只试第一个
    }
}

void solve() {
    if (!(cin >> n >> k)) return;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    sort(p, p + n, cmp_point);

    for (int i = 0; i < k; i++) r[i].valid = false;
    ans = INF;

    dfs(0);

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
