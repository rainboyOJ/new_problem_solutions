/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:03
 * update_at: 2026-10-06 13:03
 */
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 5005;

int n;                          // 矩形个数
ll raw_x1[MAXN], raw_y1[MAXN];  // 每个矩形左下角
ll raw_x2[MAXN], raw_y2[MAXN];  // 每个矩形右上角
ll xs[2 * MAXN], ys[2 * MAXN];  // x、y 方向上出现过的所有坐标（排序去重后）
int kx, ky;                     // xs、ys 去重后的坐标个数

ll dx[2 * MAXN], dy[2 * MAXN];  // dx[j]：第 j 条 x 带宽度；dy[i]：第 i 条 y 带高度
int bx1[MAXN], by1[MAXN];       // 每个矩形左/下边界所在带的起点在 xs/ys 中的下标
int bx2[MAXN], by2[MAXN];       // 每个矩形右/上边界所在带的终点在 xs/ys 中的下标

// 扫描线事件：第 row 条 y 带开始时，x 差分位置 pos 增加 inc
struct Event {
    int row;
    int pos;
    int inc;
};
Event ev[4 * MAXN];             // 每个矩形贡献 4 个事件，一共 4N 个
int ev_cnt;

ll level[2 * MAXN];             // x 方向差分数组，末尾多留一格接最右端之后的 -1
bool cover[2 * MAXN];           // 当前 y 带上每条 x 带是否被覆盖
bool prev_cover[2 * MAXN];      // 上一条 y 带的覆盖状态，最下面一行的下方视为全空

bool cmp_event(const Event &a, const Event &b) {
    return a.row < b.row;
}

// 对一维坐标排序去重，返回去重后的坐标个数，结果写回 arr
int unique_coords(ll *arr, int len) {
    std::sort(arr, arr + len);
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (k == 0 || arr[i] != arr[k - 1]) {
            arr[k] = arr[i];
            k++;
        }
    }
    return k;
}

// 在去重后的坐标数组 arr（长度 k）中查找数值 v 的下标
int find_index(ll *arr, int k, ll v) {
    int lo = 0;
    int hi = k - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] < v) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld%lld", &raw_x1[i], &raw_y1[i], &raw_x2[i], &raw_y2[i]);
        xs[2 * i - 2] = raw_x1[i];
        xs[2 * i - 1] = raw_x2[i];
        ys[2 * i - 2] = raw_y1[i];
        ys[2 * i - 1] = raw_y2[i];
    }

    // 坐标压缩：只有这些坐标会切开覆盖状态，条带内部的格子状态一致
    kx = unique_coords(xs, 2 * n);
    ky = unique_coords(ys, 2 * n);

    int nx = kx - 1;  // x 方向条带数
    int ny = ky - 1;  // y 方向条带数
    for (int j = 0; j < nx; j++) {
        dx[j] = xs[j + 1] - xs[j];
    }
    for (int i = 0; i < ny; i++) {
        dy[i] = ys[i + 1] - ys[i];
    }

    for (int i = 1; i <= n; i++) {
        bx1[i] = find_index(xs, kx, raw_x1[i]);
        bx2[i] = find_index(xs, kx, raw_x2[i]);
        by1[i] = find_index(ys, ky, raw_y1[i]);
        by2[i] = find_index(ys, ky, raw_y2[i]);
    }

    // 每个矩形拆成 4 个事件：进入时左端 +1、右端 -1，离开时施加相反的一对
    ev_cnt = 0;
    for (int i = 1; i <= n; i++) {
        ev[ev_cnt].row = by1[i]; ev[ev_cnt].pos = bx1[i]; ev[ev_cnt].inc = 1;  ev_cnt++;
        ev[ev_cnt].row = by1[i]; ev[ev_cnt].pos = bx2[i]; ev[ev_cnt].inc = -1; ev_cnt++;
        ev[ev_cnt].row = by2[i]; ev[ev_cnt].pos = bx1[i]; ev[ev_cnt].inc = -1; ev_cnt++;
        ev[ev_cnt].row = by2[i]; ev[ev_cnt].pos = bx2[i]; ev[ev_cnt].inc = 1;  ev_cnt++;
    }
    std::sort(ev, ev + ev_cnt, cmp_event);

    memset(level, 0, sizeof(level));
    memset(prev_cover, 0, sizeof(prev_cover));

    ll ans = 0;
    int ptr = 0;
    for (int row = 0; row < ny; row++) {
        // 把落在当前 y 带的事件累加到 x 差分数组上（同一位置可能叠加多个事件）
        while (ptr < ev_cnt && ev[ptr].row == row) {
            level[ev[ptr].pos] += ev[ptr].inc;
            ptr++;
        }

        // 对差分数组做前缀和，得到本行的覆盖状态
        ll running = 0;
        for (int j = 0; j < nx; j++) {
            running += level[j];
            cover[j] = running > 0;
        }

        // 水平边：与上一行状态不同的条带，整段露出边界
        ll horizontal = 0;
        for (int j = 0; j < nx; j++) {
            if (cover[j] != prev_cover[j]) {
                horizontal += dx[j];
            }
        }

        // 竖直边：本行左右两端 + 行内状态翻转处，乘以行高
        ll border = 0;
        if (cover[0]) {
            border++;
        }
        if (cover[nx - 1]) {
            border++;
        }
        for (int j = 1; j < nx; j++) {
            if (cover[j] != cover[j - 1]) {
                border++;
            }
        }

        ans += horizontal + dy[row] * border;

        for (int j = 0; j < nx; j++) {
            prev_cover[j] = cover[j];
        }
    }

    // 最上面一行之上没有矩形，顶部整条边界都要累加
    for (int j = 0; j < nx; j++) {
        if (prev_cover[j]) {
            ans += dx[j];
        }
    }

    printf("%lld\n", ans);
    return 0;
}
