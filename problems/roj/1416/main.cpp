/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-17 22:52
 * update_at: 2026-10-17 22:52
 */
// main.cpp：静态「矩形覆盖计数」——扫描线 + 树状数组。
//
// 矩形是半开的 [l,r) x [d,u)。把「覆盖次数」沿 x 方向拆成两个事件：
//   x = l 处对 y 区间 [d,u) 加 1（矩形从这里进入扫描线）
//   x = r 处对 y 区间 [d,u) 减 1（矩形从这里离开扫描线）
// 所有事件按 x 升序扫描，同一 x 先做矩形事件再回答询问：
// 这样 x == l 的矩形已经加进来、x == r 的矩形已经减掉，恰好是半开区间。
//
// y 方向用「差分 + 树状数组」：区间加变成两次单点加，单点查变成一次前缀和，
// 每个事件只要 O(log) 时间，总复杂度 O((N + M) log (N + M))。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXE = 3 * MAXN; // 事件上限：2N 个矩形事件 + M 个询问（N、M <= 1e5）

// 一个事件要么是矩形在 x 处的进出，要么是一个询问点
struct Event {
    int x;      // 事件发生的 x 坐标
    int kind;   // 0 = 矩形事件，1 = 询问
    int sign;   // 矩形事件：+1 表示在 x 处进入，-1 表示在 x 处离开
    int lo;     // 矩形事件的 y 区间下界（已离散化，闭）
    int hi;     // 矩形事件的 y 区间上界（已离散化，开）
    int y;      // 询问点的 y（已离散化）
    int id;     // 询问编号，按输入顺序输出
};

Event ev[MAXE]; // 所有事件，最后按 x 升序扫描
int ev_cnt;     // 事件个数

int ys[MAXE];  // 离散化用的 y 坐标：矩形的上下边界 + 询问点的 y
int ys_cnt;    // 去重后的 y 个数，也是树状数组长度
int ans[MAXN]; // ans[j]：第 j 个询问的覆盖矩形个数
int bit[MAXE]; // 树状数组：维护 y 方向差分数组，区间加两次单点加即可

// 登记一个矩形事件：在 x 处把 y 区间 [lo, hi) 加上 sign
void add_rect_event(int x, int sign, int lo, int hi) {
    ev_cnt++;
    ev[ev_cnt].x = x;
    ev[ev_cnt].kind = 0;
    ev[ev_cnt].sign = sign;
    ev[ev_cnt].lo = lo;
    ev[ev_cnt].hi = hi;
    ev[ev_cnt].y = 0;
    ev[ev_cnt].id = 0;
}

// 登记一个询问事件：在 x 处查询点 (x, y)
void add_query_event(int x, int y, int id) {
    ev_cnt++;
    ev[ev_cnt].x = x;
    ev[ev_cnt].kind = 1;
    ev[ev_cnt].sign = 0;
    ev[ev_cnt].lo = 0;
    ev[ev_cnt].hi = 0;
    ev[ev_cnt].y = y;
    ev[ev_cnt].id = id;
}

// 事件排序：x 升序；x 相同则矩形事件（kind = 0）排在询问前面
bool cmp_event(Event a, Event b) {
    if (a.x != b.x) return a.x < b.x;
    return a.kind < b.kind;
}

// 树状数组：单点加
void bit_add(int i, int v) {
    for (; i <= ys_cnt; i += i & -i) bit[i] += v;
}

// 树状数组：前缀和，即 y 方向差分数组前 i 项之和 = 第 i 个 y 坐标处的覆盖次数
int bit_sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}

// 在离散化数组 ys[1..ys_cnt] 中找第一个 >= v 的位置（1 下标）
int lower_id(int v) {
    return lower_bound(ys + 1, ys + ys_cnt + 1, v) - ys;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 先把矩形和询问读进来：y 坐标要整体离散化，必须先读完才知道有哪些值
    int rl[MAXN], rd[MAXN], rr[MAXN], ru[MAXN]; // 第 i 个矩形的 l、d、r、u
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d %d", &rl[i], &rd[i], &rr[i], &ru[i]);
        ys[++ys_cnt] = rd[i];
        ys[++ys_cnt] = ru[i];
    }
    int qx[MAXN], qy[MAXN];
    for (int j = 1; j <= m; j++) {
        scanf("%d %d", &qx[j], &qy[j]);
        ys[++ys_cnt] = qy[j];
    }

    // y 离散化：排序去重
    sort(ys + 1, ys + ys_cnt + 1);
    ys_cnt = unique(ys + 1, ys + ys_cnt + 1) - (ys + 1);

    // 建事件：每个矩形拆成「进」「出」两个，每个询问一个
    for (int i = 1; i <= n; i++) {
        int lo = lower_id(rd[i]); // d 的位置：覆盖判定从这里开始
        int hi = lower_id(ru[i]); // u 的位置：覆盖判定到这里结束（开）
        add_rect_event(rl[i], +1, lo, hi);
        add_rect_event(rr[i], -1, lo, hi);
    }
    for (int j = 1; j <= m; j++) add_query_event(qx[j], lower_id(qy[j]), j);

    // 扫描线：按 x 从小到大处理所有事件
    sort(ev + 1, ev + ev_cnt + 1, cmp_event);
    for (int i = 1; i <= ev_cnt; i++) {
        if (ev[i].kind == 0) {
            // 区间加 [lo, hi)：差分上就是 lo 处加、hi 处减
            bit_add(ev[i].lo, ev[i].sign);
            bit_add(ev[i].hi, -ev[i].sign);
        } else {
            // 单点查：前缀和就是 y 处当前被多少个矩形覆盖
            ans[ev[i].id] = bit_sum(ev[i].y);
        }
    }

    for (int j = 1; j <= m; j++) printf("%d\n", ans[j]);
    return 0;
}
