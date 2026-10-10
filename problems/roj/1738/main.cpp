// Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
// rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
// rainboy的学习导航网站: https://idx.roj.ac.cn
// create_at: 2026-10-08 10:20
// update_at: 2026-10-08 10:20
//
// ROJ 1738《圆桌聚会》
// 座位圈 x_0..x_{2n-1} 需满足 x_{i+1} ≡ 2*x_i + k (mod 2n)，k∈{0,1}。
// 把数字 0..2n-1 看成边：弧 a_y 从顶点 y/2 指向顶点 y mod n（顶点集 Z_n）。
// 每个顶点出度=入度=2，故存在欧拉回路；弧标号序列即合法座位圈。
// Hierholzer 迭代实现（显式栈，防爆系统栈），每条边只走一次，O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static const int MAXN = 500000;          // n 的上界
static char used[MAXN];                  // 顶点 v 已经走过的出弧数（0..2）
static int stk[2 * MAXN + 5];            // 显式栈：栈元素是「进入当前顶点的弧号」，起点为 -1
static int path[2 * MAXN + 5];           // 回溯时记录的弧号，逆访问序

static char outbuf[1 << 23];             // 输出缓冲
static int outpos = 0;

/** 把非负整数写进输出缓冲，缓冲将满时先落盘。 */
inline void writeInt(int x) {
    if (outpos > (1 << 23) - 32) { fwrite(outbuf, 1, outpos, stdout); outpos = 0; }
    char tmp[12];
    int len = 0;
    if (x == 0) tmp[len++] = '0';
    while (x > 0) { tmp[len++] = char('0' + x % 10); x /= 10; }
    while (len--) outbuf[outpos++] = tmp[len];
}

int main() {
    // 输入只有若干行整数，整块读入后自己扫数字，比 cin/scanf 逐个解析快得多
    string inbuf;
    {
        char chunk[1 << 16];
        size_t got;
        while ((got = fread(chunk, 1, sizeof(chunk), stdin)) > 0) inbuf.append(chunk, got);
    }
    inbuf.push_back('\0');

    char *p = &inbuf[0];
    while (true) {
        while (*p && (*p < '0' || *p > '9')) ++p;   // 跳过空白等分隔符
        if (*p == '\0') break;
        int n = 0;
        while (*p >= '0' && *p <= '9') n = n * 10 + (*p++ - '0');
        if (n <= 0) continue;

        for (int i = 0; i < n; i++) used[i] = 0;    // 只清 0..n-1，避免 O(T*MAXN)

        int top = 0, cnt = 0;
        stk[top++] = -1;                            // 起点 0 没有「进入它的弧」
        while (top > 0) {
            int a = stk[top - 1];                   // 当前所在的弧
            int v = (a < 0) ? 0 : a % n;            // 弧 a 的头 = a mod n
            if (used[v] < 2) {                      // 还有没走过的出弧，就继续深入
                int y = 2 * v + used[v]++;
                stk[top++] = y;
            } else {                                // 出弧走完，回溯时登记进来的那条弧
                path[cnt++] = a;
                --top;
            }
        }

        // path 是逆访问序，最后一项是起点哨兵 -1；倒着输出即为欧拉回路的弧序列
        for (int i = cnt - 2; i >= 0; --i) {
            if (i != cnt - 2) outbuf[outpos++] = ' ';
            writeInt(path[i]);
        }
        outbuf[outpos++] = '\n';
    }

    if (outpos) fwrite(outbuf, 1, outpos, stdout);
    return 0;
}
