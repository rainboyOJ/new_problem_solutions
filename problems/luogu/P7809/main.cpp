#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXLOG = 21;
const int BUF_SIZE = 1 << 20;

int n, m;
unsigned char a[MAXN];
int pre_one[MAXN];
int lg2_table[MAXN];
int f[MAXN];                   // f[i] = i - 2 * 前 i 个 1 的个数
int st[MAXLOG][MAXN];          // 区间最大值 ST 表，维护 f
int next_zero[MAXN];
int prev_one_pos[MAXN];
char outbuf[BUF_SIZE];
int outpos = 0;

namespace FastIO {
char inbuf[BUF_SIZE];
int inpos = 0;
int inlen = 0;

inline int gc() {
    if (inpos == inlen) {
        inlen = fread(inbuf, 1, BUF_SIZE, stdin);
        inpos = 0;
        if (inlen == 0) {
            return EOF;
        }
    }
    return inbuf[inpos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    int sign = 1;
    int c = gc();
    while (c != '-' && (c < '0' || c > '9')) {
        c = gc();
    }
    if (c == '-') {
        sign = -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = gc();
    }
    x *= sign;
}
}

inline void flush_output() {
    fwrite(outbuf, 1, outpos, stdout);
    outpos = 0;
}

inline void put_char(int c) {
    if (outpos == BUF_SIZE) {
        flush_output();
    }
    outbuf[outpos++] = (char)c;
}

inline void write_int(int x) {
    if (x == 0) {
        put_char('0');
        put_char('\n');
        return;
    }
    if (x < 0) {
        put_char('-');
        x = -x;
    }
    char s[20];
    int len = 0;
    while (x > 0) {
        s[len++] = (char)('0' + x % 10);
        x /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        put_char(s[i]);
    }
    put_char('\n');
}

void build_logs() {
    lg2_table[1] = 0;
    for (int i = 2; i <= n + 1; i++) {
        lg2_table[i] = lg2_table[i >> 1] + 1;
    }
}

void build_sparse_table() {
    for (int i = 0; i <= n; i++) {
        st[0][i] = f[i];
    }

    for (int k = 1; k < MAXLOG; k++) {
        int len = 1 << k;
        int half = len >> 1;
        if (len > n + 1) {
            break;
        }
        for (int i = 0; i + len - 1 <= n; i++) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + half]);
        }
    }
}

inline int query_max(int l, int r) {
    int k = lg2_table[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

inline int solve_non_decreasing(int l, int r) {
    // 枚举“0 段”和“1 段”的分界点 k：
    // 取 [l, k] 中所有 0，再取 [k+1, r] 中所有 1。
    int best = query_max(l - 1, r);
    return pre_one[l - 1] + pre_one[r] - l + 1 + best;
}

inline int solve_increasing(int l, int r) {
    // 01 串的严格上升子序列只可能是 0,1，长度最多为 2。
    // 只要区间里存在一个 0 在某个 1 前面，答案就是 2，否则是 1。
    if (next_zero[l] < prev_one_pos[r]) {
        return 2;
    }
    return 1;
}

int main() {
    FastIO::read(n);
    FastIO::read(m);

    pre_one[0] = 0;
    prev_one_pos[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        FastIO::read(x);
        a[i] = (unsigned char)x;
        pre_one[i] = pre_one[i - 1] + x;
        prev_one_pos[i] = (x == 1 ? i : prev_one_pos[i - 1]);
    }

    next_zero[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
        if (a[i] == 0) {
            next_zero[i] = i;
        }
        else {
            next_zero[i] = next_zero[i + 1];
        }
    }

    for (int i = 0; i <= n; i++) {
        f[i] = i - (pre_one[i] << 1);
    }

    build_logs();
    build_sparse_table();

    for (int i = 1; i <= m; i++) {
        int op, l, r;
        FastIO::read(op);
        FastIO::read(l);
        FastIO::read(r);

        if (op == 1) {
            write_int(solve_non_decreasing(l, r));
        }
        else {
            write_int(solve_increasing(l, r));
        }
    }

    flush_output();
    return 0;
}
