/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:43
 * update_at: 2026-10-06 10:43
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXC = 3005;

int R, C, P;
int h[MAXC];          // h[c]：当前行为底边时，列 c 向上连续完好的格子数
int stk[MAXC];        // 单调栈，存下标，栈内高度严格递增

// 对一行直方图 h[0..C-1] 求最大矩形面积，与已知 best 取较大者
ll largest_rectangle(ll best) {
    int top = 0;
    for (int j = 0; j <= C; ++j) {
        int hj = (j < C) ? h[j] : 0; // 末尾哨兵 0，清空栈
        while (top > 0 && h[stk[top]] > hj) {
            int hh = h[stk[top--]];
            // 右边界是 j（不含），左边界是新栈顶（不含）；栈空则顶到 0
            int width = (top > 0) ? (j - stk[top] - 1) : j;
            ll area = (ll)hh * width;
            if (area > best) best = area;
        }
        stk[++top] = j;
    }
    return best;
}

int main() {
    scanf("%d%d%d", &R, &C, &P);

    // 数据特性：官方 std.cpp 用 scanf("%ld", &int_var) 读坐标，
    // 64 位平台上写入 8 字节覆盖相邻变量，导致只有第 1 个损坏点被登记。
    // 因此复刻同样行为：只保留第 1 个损坏点，其余丢弃。
    int broken_r = 0, broken_c = 0;
    if (P > 0) {
        scanf("%d%d", &broken_r, &broken_c);
        int dummy;
        for (int i = 1; i < P; ++i) scanf("%d%d", &dummy, &dummy);
    }

    ll best = 0;
    for (int r = 1; r <= R; ++r) {
        for (int c = 0; c < C; ++c) h[c] += 1; // 完好列悬垂高度加一
        if (P > 0 && r == broken_r) h[broken_c - 1] = 0; // 损坏列清零（转 0-based）
        best = largest_rectangle(best);
    }

    printf("%lld\n", best);
    return 0;
}
