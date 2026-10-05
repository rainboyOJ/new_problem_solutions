/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:13
 * update_at: 2026-10-05 12:13
 */
// main.cpp：单调队列做二维滑动窗口最值，求最小的「n×n 方格最大值 − 最小值」。
// 先对每行横向滑窗得到行窗口最值表，再对行窗口表的每列纵向滑窗，
// 两次 min 复合还是方格最小值，两次 max 复合还是方格最大值。
#include <cstdio>

typedef long long ll;

const int MAXN = 1005; // 矩阵长宽上限

ll a, b, n;              // a 行、b 列、正方形边长 n
int line[MAXN];          // 当前读入的一行原始数据，压完即弃，不保存整个矩阵
int row_min[MAXN][MAXN]; // row_min[r][c]：第 r 行 [c, c+n) 的最小值（行窗口表）
int row_max[MAXN][MAXN]; // row_max[r][c]：第 r 行 [c, c+n) 的最大值（行窗口表）
ll q[MAXN];              // 单调队列，存下标，对应值按 mode 保持单调
int col_min[MAXN];       // 当前这一列纵向滑窗得到的方格最小值
int col_max[MAXN];       // 当前这一列纵向滑窗得到的方格最大值
int tmp[MAXN];           // 纵向滑窗时暂存的一列

// 对 src[1..len] 做长度 k 的滑动窗口最值，结果依次写入 dst[1..len-k+1]。
// mode = 0 求最小值，mode = 1 求最大值。
void window_best(int *src, ll len, ll k, int mode, int *dst) {
    ll head = 1; // 队首指针
    ll tail = 0; // 队尾指针，head > tail 表示队空
    ll cnt = 0;  // 已产出的窗口个数
    for (ll i = 1; i <= len; i++) {
        while (head <= tail) {
            ll back = q[tail];
            // 队尾被新值支配：求 min 时队尾 >= 新值（取等也弹，新下标更靠右、更晚过期）
            bool remove = (mode == 0 ? src[back] >= src[i] : src[back] <= src[i]);
            if (!remove) break;
            tail--;
        }
        q[++tail] = i;
        if (q[head] <= i - k) head++; // 队首下标已滑出窗口
        if (i >= k) dst[++cnt] = src[q[head]];
    }
}

int main() {
    scanf("%lld%lld%lld", &a, &b, &n);
    for (ll r = 1; r <= a; r++) {
        for (ll c = 1; c <= b; c++) {
            scanf("%d", &line[c]);
        }
        window_best(line, b, n, 0, row_min[r]);
        window_best(line, b, n, 1, row_max[r]);
    }

    ll width = b - n + 1;   // 每行可以放下的正方形个数
    ll height = a - n + 1;  // 每列可以放下的正方形个数
    ll ans = 2000000000LL;  // 差值上界 1e9，先放一个更大的数再逐格收紧
    for (ll c = 1; c <= width; c++) {
        for (ll r = 1; r <= a; r++) tmp[r] = row_min[r][c];
        window_best(tmp, a, n, 0, col_min);
        for (ll r = 1; r <= a; r++) tmp[r] = row_max[r][c];
        window_best(tmp, a, n, 1, col_max);
        for (ll i = 1; i <= height; i++) {
            ll diff = col_max[i] - col_min[i]; // 左上角为 (i, c) 的 n×n 方格差值
            if (diff < ans) ans = diff;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
