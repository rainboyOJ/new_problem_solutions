/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:16
 */
// P9715 「QFOI R1」头：正解。
// 关键结论：一个格子最后的颜色，等于覆盖它的最后一个 t=1 操作的颜色；
// 如果没有任何 t=1 操作覆盖它，则等于覆盖它的第一个操作（必为 t=0）的颜色。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2000005;   // 行 / 列下标上限
const int MAXQ = 2000005;   // 操作数上限
const int MAXK = 500005;    // 颜色数上限

int n, m, k, q;             // 行数、列数、颜色数、操作数

int L[MAXQ], R[MAXQ];       // 第 i 个操作的区间 [L[i], R[i]]
int colOf[MAXQ];            // 第 i 个操作使用的颜色
// kind[i]：0 = 涂行且 t=0，1 = 涂行且 t=1，2 = 涂列且 t=0，3 = 涂列且 t=1
unsigned char kind[MAXQ];

int lastRow1[MAXN];         // lastRow1[x]：最后一个整行覆盖第 x 行的 t=1 操作编号，0 表示没有
int lastCol1[MAXN];         // lastCol1[x]：最后一个整列覆盖第 x 列的 t=1 操作编号，0 表示没有

// val[i]：第 i 个操作在这一遍扫描中“新确定”的行数（涂行）或列数（涂列）
int val[MAXQ];

// 并查集：nxtR[x] 指向 >= x 的第一个还没被“确定”的行，nxtC 同理作用在列上
int nxtR[MAXN], nxtC[MAXN];

ll ans[MAXK];               // ans[c]：颜色 c 最终覆盖的格子数

// ---------- 快速读入 ----------
char buf[1 << 16];
int bufPos = 0, bufLen = 0;

inline char getch() {
    if (bufPos == bufLen) {
        bufLen = (int)fread(buf, 1, 1 << 16, stdin);
        bufPos = 0;
        if (bufLen <= 0) return 0;
    }
    return buf[bufPos++];
}

inline int readInt() {
    char ch = getch();
    while (ch < '0' || ch > '9') {
        if (ch == 0) return -1;
        ch = getch();
    }
    int x = 0;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getch();
    }
    return x;
}

// 返回 >= x 的第一个还没被确定的行（路径压缩的迭代写法）
int findR(int x) {
    while (nxtR[x] != x) {
        nxtR[x] = nxtR[nxtR[x]];
        x = nxtR[x];
    }
    return x;
}

// 返回 >= x 的第一个还没被确定的列
int findC(int x) {
    while (nxtC[x] != x) {
        nxtC[x] = nxtC[nxtC[x]];
        x = nxtC[x];
    }
    return x;
}

void read_data() {
    n = readInt();
    m = readInt();
    k = readInt();
    q = readInt();
    for (int i = 1; i <= q; i++) {
        int op = readInt();
        L[i] = readInt();
        R[i] = readInt();
        colOf[i] = readInt();
        int t = readInt();
        kind[i] = (unsigned char)((op - 1) * 2 + t);
    }
}

// 倒序扫描：确定每个 t=1 操作是哪些行 / 列的“最后一次覆盖”
void sweep_last() {
    for (int i = 1; i <= n + 1; i++) nxtR[i] = i;
    for (int i = 1; i <= m + 1; i++) nxtC[i] = i;

    for (int i = q; i >= 1; i--) {
        if ((kind[i] & 1) == 0) continue;   // 只处理 t=1
        int l = L[i], r = R[i];
        if (kind[i] <= 1) {                 // 涂行
            int cnt = 0;
            int x = findR(l);
            while (x <= r) {
                lastRow1[x] = i;
                cnt++;
                nxtR[x] = x + 1;            // 这一行已经确定，从并查集里删掉
                x = findR(x + 1);
            }
            val[i] = cnt;
        } else {                            // 涂列
            int cnt = 0;
            int x = findC(l);
            while (x <= r) {
                lastCol1[x] = i;
                cnt++;
                nxtC[x] = x + 1;
                x = findC(x + 1);
            }
            val[i] = cnt;
        }
    }
}

// 正序扫描：确定每个 t=0 操作是哪些行 / 列的“第一次覆盖”
// 只有从未被 t=1 覆盖过的行 / 列，才可能作为“第一次涂色”的来源
void sweep_first() {
    for (int i = 1; i <= n + 1; i++) nxtR[i] = i;
    for (int i = 1; i <= m + 1; i++) nxtC[i] = i;

    for (int i = 1; i <= q; i++) {
        if ((kind[i] & 1) != 0) continue;   // 只处理 t=0
        int l = L[i], r = R[i];
        if (kind[i] <= 1) {                 // 涂行
            int cnt = 0;
            int x = findR(l);
            while (x <= r) {
                if (lastRow1[x] == 0) cnt++;
                nxtR[x] = x + 1;
                x = findR(x + 1);
            }
            val[i] = cnt;
        } else {                            // 涂列
            int cnt = 0;
            int x = findC(l);
            while (x <= r) {
                if (lastCol1[x] == 0) cnt++;
                nxtC[x] = x + 1;
                x = findC(x + 1);
            }
            val[i] = cnt;
        }
    }
}

// 正序累加答案
// C = 当前 lastRow1 < i 的行数；A = 当前 lastCol1 < i 的列数
// D = 当前“第一次覆盖” < i 的纯 t=0 行数；B = 当前“第一次覆盖” < i 的纯 t=0 列数
void calc_answer() {
    ll C = 0, A = 0, D = 0, B = 0;
    for (int i = 1; i <= n; i++) if (lastRow1[i] == 0) C++;   // C 的初值就是 n0
    for (int i = 1; i <= m; i++) if (lastCol1[i] == 0) A++;   // A 的初值就是 m0
    ll n0 = C, m0 = A;

    for (int i = 1; i <= q; i++) {
        int c = colOf[i];
        if (kind[i] <= 1) {                 // 涂行
            if (kind[i] == 1) {             // t=1：这些格子由本操作最后覆盖
                ans[c] += (ll)val[i] * A;
                C += val[i];
            } else {                        // t=0：这些格子是“第一次被涂”
                ans[c] += (ll)val[i] * (m0 - B);
                D += val[i];
            }
        } else {                            // 涂列
            if (kind[i] == 3) {             // t=1
                ans[c] += (ll)val[i] * C;
                A += val[i];
            } else {                        // t=0
                ans[c] += (ll)val[i] * (n0 - D);
                B += val[i];
            }
        }
    }
}

int main() {
    read_data();
    sweep_last();
    sweep_first();
    calc_answer();

    for (int i = 1; i <= k; i++) {
        printf("%lld", ans[i]);
        putchar(i == k ? '\n' : ' ');
    }
    return 0;
}
