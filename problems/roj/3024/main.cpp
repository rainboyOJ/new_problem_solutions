/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:36
 * update_at: 2026-10-06 14:36
 */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

// 二色最近点对：核电站-特工才算答案，同色点对一律跳过。
// 套用经典最近点对分治骨架，关键差异是把跨色最优平方距离 best
// 作为参数一路"下传"递归（而不是取左右两半各自答案的 min），
// 否则同色点挤成一团时会把窄条剪成一条缝、漏掉真正的跨色点对。

const int MAXN = 200005; // 每组最多 2n 个点，n <= 100000

struct P {
    ll x, y;
    int c; // 颜色：0 = 核电站，1 = 特工
};

P a[MAXN];     // a[1..2n] 存本组所有点，进入递归前按 x 排序，递归会把区间整理成按 y 有序
P tmp[MAXN];   // 归并两半用的临时数组
P strip[MAXN]; // 距分割线水平距离的平方 < best 的窄条内的点（按 y 升序）

bool cmp_p(const P &u, const P &v) {
    if (u.x != v.x) return u.x < v.x;
    return u.y < v.y;
}

// 两点距离的平方：全程用整数比较，坐标 1e9 级别时平方和 < 2^63，不会溢出
ll sq_dist(const P &u, const P &v) {
    ll dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}

// 分治处理 a[l..r)：best 是当前已知的跨色最小平方距离，只会变小、不会漏解。
// 返回更新后的 best，同时把 a[l..r) 整理成按 y 升序，供上层归并。
ll divide(int l, int r, ll best) {
    if (r - l <= 1) return best; // 0 或 1 个点，区间内无从比较
    int mid = (l + r) / 2;
    ll midx = a[mid].x; // 分割竖线 x = midx，必须在递归前记下（递归会打乱 a）

    best = divide(l, mid, best);
    best = divide(mid, r, best);

    // 归并两半（各自已按 y 升序），使 a[l..r) 整体按 y 升序
    int p = l, q = mid, t = l;
    while (p < mid && q < r) {
        if (a[p].y <= a[q].y) tmp[t++] = a[p++];
        else tmp[t++] = a[q++];
    }
    while (p < mid) tmp[t++] = a[p++];
    while (q < r) tmp[t++] = a[q++];
    for (int i = l; i < r; i++) a[i] = tmp[i];

    // 更近的跨色点对两端点的 x 都必须落在分割线两侧宽 sqrt(best) 的窄条内：
    // 否则 dx >= sqrt(best)，距离不可能更优。strip 已按 y 升序。
    int m = 0;
    for (int i = l; i < r; i++) {
        ll dx = a[i].x - midx;
        if (dx * dx < best) strip[m++] = a[i];
    }

    // 窗口扫描：对每个点只向后看，一旦 y 差平方 >= best 就 break
    // （后面的点 y 只会更大，全部可以放弃）；同色点对直接跳过。
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            ll dy = strip[j].y - strip[i].y;
            if (dy * dy >= best) break;
            if (strip[i].c == strip[j].c) continue; // 同色不计入答案
            best = min(best, sq_dist(strip[i], strip[j]));
        }
    }
    return best;
}

int main() {
    int T;
    scanf("%d", &T);
    srand(20261006); // 固定随机种子，行为可复现
    while (T--) {
        int n;
        scanf("%d", &n);
        // 前 n 个是核电站（a[1..n]），后 n 个是特工（a[n+1..2n]）
        for (int i = 1; i <= 2 * n; i++) {
            scanf("%lld%lld", &a[i].x, &a[i].y);
            a[i].c = (i <= n) ? 0 : 1;
        }

        // 开局随机抽 1000 对（电站, 特工），取最小平方距离当初始上界：
        // 保证 best 一开始就是某个真实跨色点对的距离（n=1 的边界也天然正确），
        // 剪枝半径从一开始就有限
        ll best = -1;
        for (int k = 0; k < 1000; k++) {
            int i = rand() % n + 1;
            int j = rand() % n + 1;
            ll d = sq_dist(a[i], a[n + j]);
            if (best == -1 || d < best) best = d;
        }

        sort(a + 1, a + 2 * n + 1, cmp_p);
        best = divide(1, 2 * n + 1, best);
        printf("%.3f\n", sqrt((double)best));
    }
    return 0;
}
