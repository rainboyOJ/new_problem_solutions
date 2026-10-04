/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:06
 * update_at: 2026-10-04 23:06
 */
// main.cpp：roj 10022 网络
// 题设保证每个点的前驱集合 H[i] 是团，即编号 1..n 是弦图的一个完美消除序列。
// 记 P(i) = {i} ∪ H[i]，它是包含 i 的最大团；极大团恰好是那些不被其它 P(j) 包住的 P(i)。
// 若 j = last[i]（i 的最大前驱），由 H[i] 是团可得 H[i]\{j} ⊆ H[j]，
// 于是 |H[i]| > |H[j]| 等价于 P(j) ⊆ P(i)，即 j 对应的团被 i 吸收。
// 所以按 i 扫一遍、用一次整数比较标记被吸收的 j，答案就是 n 减去被标记点的个数。
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;

const ll MAXN = 1000005; // n <= 1e6
const ll MAXM = 1000005; // m <= 1e6
const ll SHIFT = 20;     // n <= 1e6 < 2^20，把一条边压成 a<<SHIFT|b

ll n, m;
ll packed_edge[MAXM]; // 每条边压缩为 a<<SHIFT|b，排序后既去重、又保证同一终点的前驱按起点升序
int pred_cnt[MAXN];   // pred_cnt[i] = |H[i]|，去重后 i 的不同前驱个数（<= 1e6，用 int 省内存）
int pred_max[MAXN];   // pred_max[i] = max H[i]，即 i 的最大前驱 last[i]，0 表示没有前驱
char covered[MAXN];   // covered[j] = 1 表示 P(j) 被更大的团包住，不是极大团（标记只有 0/1，用 char）

const int BUF_SIZE = 1 << 20;
char in_buf[BUF_SIZE]; // fread 输入缓冲：最多 2e6 个整数，cin 会超时
int buf_pos = 0, buf_len = 0;

// 从缓冲区取一个字符，缓冲区读空时用 fread 续读；输入结束返回 -1。
int read_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(in_buf, 1, BUF_SIZE, stdin);
        buf_pos = 0;
        if (buf_len <= 0) return -1;
    }
    return in_buf[buf_pos++];
}

// 快读一个非负整数。
ll read_int() {
    int c = read_char();
    while (c <= ' ' && c != -1) c = read_char();
    ll x = 0;
    while (c > ' ') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    return x;
}

void read_input() {
    n = read_int();
    m = read_int();
    for (ll i = 0; i < m; i++) {
        ll a = read_int();
        ll b = read_int();
        packed_edge[i] = (a << SHIFT) | b; // a 占高位、b 占低 20 位，按 (a,b) 字典序排序
    }
}

int main() {
    read_input();

    sort(packed_edge, packed_edge + m);

    // 排序后相同边相邻，跳过重复边完成去重；
    // 同一个终点 b 的边按起点 a 升序出现，最后一次写入的 a 就是最大前驱。
    ll seen = -1;
    for (ll i = 0; i < m; i++) {
        if (packed_edge[i] == seen) continue;
        seen = packed_edge[i];
        int b = packed_edge[i] & ((1 << SHIFT) - 1);
        pred_cnt[b] = pred_cnt[b] + 1;
        pred_max[b] = packed_edge[i] >> SHIFT;
    }

    // P(i) = {i} ∪ H[i] 是包含 i 的最大团，极大团与未被包住的 P(i) 一一对应。
    // 若 last[i] = j 且 |H[i]| > |H[j]|，则 H[i] = H[j] ∪ {j}，有 P(j) ⊆ P(i)，j 被吸收。
    for (ll i = 1; i <= n; i++) {
        int j = pred_max[i];
        if (j != 0 && pred_cnt[i] > pred_cnt[j]) {
            covered[j] = 1;
        }
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (covered[i] == 0) ans = ans + 1;
    }
    printf("%lld\n", ans);

    return 0;
}
