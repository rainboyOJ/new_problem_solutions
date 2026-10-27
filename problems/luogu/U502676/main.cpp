/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 17:04
 * update_at: 2026-10-27 17:04
 */
// main.cpp：正解。线段树维护区间最大值，查询时带着"子树里还有没有大于 k 的数"这个判据单路下降，每次 O(log n)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2000000 + 5;
const int MAXNODE = MAXN * 4;

int n, m;
int a[MAXN];  // a[i] 只有 2e6 以内且只做大小比较，用 int 省内存
int mx[MAXNODE]; // mx[p]：结点 p 覆盖区间里的最大值

// 输入输出可达 30MB、约 5e6 个整数，cin/cout 在这道题的时限下不够用，改为手写读写
const int BUFSIZE = 1 << 16;
char in_buf[BUFSIZE];
int in_len = 0;
int in_pos = 0;

inline char read_char() {
    if (in_pos == in_len) {
        in_len = fread(in_buf, 1, BUFSIZE, stdin);
        in_pos = 0;
        if (in_len <= 0) return 0;
    }
    return in_buf[in_pos++];
}

inline int read_int() {
    char c = read_char();
    while (c != 0 && (c < '0' || c > '9')) c = read_char();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = read_char();
    }
    return x;
}

char out_buf[BUFSIZE];
int out_len = 0;

inline void write_int(int x) {
    if (out_len + 16 > BUFSIZE) {
        fwrite(out_buf, 1, out_len, stdout);
        out_len = 0;
    }
    if (x < 0) {
        out_buf[out_len++] = '-';
        x = -x;
    }
    char tmp[16];
    int len = 0;
    do {
        tmp[len++] = char('0' + x % 10);
        x /= 10;
    } while (x > 0);
    while (len > 0) out_buf[out_len++] = tmp[--len];
    out_buf[out_len++] = '\n';
}

// 上推：父结点的最大值取两个儿子的较大者
void push_up(int p) {
    mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
}

void build(int p, int l, int r) {
    if (l == r) {
        mx[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// 在位置区间 [ql, qr] 中找第一个 a[i] > k 的下标，找不到返回 -1
// 关键判据：mx[p] <= k 说明整段都不可能有答案，直接剪掉，不再往下走
int query_first(int p, int l, int r, int ql, int qr, int k) {
    if (qr < l || r < ql) return -1; // 这一段和询问区间不相交
    if (mx[p] <= k) return -1;       // 这一段的最大值都不大于 k，整段无解
    if (l == r) return l;            // 走到叶子，且它一定大于 k

    int mid = (l + r) >> 1;
    int answer = query_first(p << 1, l, mid, ql, qr, k); // 左边优先，保证取到最靠左的答案
    if (answer != -1) return answer;
    return query_first(p << 1 | 1, mid + 1, r, ql, qr, k);
}

int main() {
    n = read_int();
    m = read_int();
    for (int i = 1; i <= n; i++) a[i] = read_int();
    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int l = read_int();
        int r = read_int();
        int k = read_int();
        write_int(query_first(1, 1, n, l, r, k));
    }

    if (out_len > 0) fwrite(out_buf, 1, out_len, stdout);
    return 0;
}
