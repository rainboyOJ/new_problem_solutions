/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 17:40
 */
// P9717 [EC Final 2022] Binary String
//
// 每一步同时把所有 01 换成 10。把 1 看成向左走的粒子（左边是 0 就走一格，
// 否则原地等待），整个过程就是环上的 TASEP（等价于 Rule 184）。
//
// 【状态图是 ρ 形】状态只会沿着一条链前进，很快进入一个纯旋转的环：环里的
// 每个串都是终态的循环移位，环长 = 终态这个循环串的最小周期 P；进环前走过
// 的步数是 T（初始串算第 0 步）。于是不同的串一共有 T + P 个。
//
// 【把 1 变多】若 0 比 1 多，就把 01 取反再整体反转。交换规则在这个变换下
// 不变（01 -> 10 与 10 -> 01 互相对应），所以 T、P 都不变。
//
// 【破环为链：Raney 引理】在环上，最左边的那个 0 段可能要靠串尾的 1 段绕一
// 圈才能吃掉。把 1 记 +1、0 记 -1 做前缀和，从"前缀和首次取到最小值"的位置
// 之后把环切开，可以保证任意前缀里 1 的个数不少于 0 的个数，于是串尾的 1 段
// 一定能一路向左吃光所有 0 段，环上的麻烦就消失了。
//
// 【栈模拟段相撞】从右往左扫，用一个栈维护还没被吃掉的 01 段（左端点、长度）。
// 长度 > 1 的 1 段整体右移，长度 > 1 的 0 段整体左移；两者相遇后交界处每秒各
// 减 1，直到其中一段消失。设当前 1 段长度 c、左端点 i+1，栈顶 0 段长度 k、
// 左端点 l，则这段相撞结束（也就是"两个段的端点相遇"）所需的秒数 r 为：
//     k > c  ： 1 段被吃光，r = (l - 1 - i - c) / 2
//     k <= c ： 0 段被吃光，r = (l + 2k - 1 - i - c) / 2
// 取所有相撞事件里最大的 r，得到 mx = T + 1（r 的推导见题解正文）。
//
// 【还原终态】栈里剩下的 1 段就是终态里的那些 1 段，把它们整体按 mx-1 反向
// 偏移，空隙用 01 交替补齐，就得到环上的一个确定串。
//
// 【KMP 求 P】环长就是该串的最小整周期。把串复制一遍接在后面，用 KMP 求
// 最小周期 P = 2n - fail[2n]，答案就是 T + P = (mx - 1) + P。
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 10000000 + 10;

static char inbuf[1 << 25];      // 一次性读入全部输入
static char s[MAXN];             // 当前串
static int  failArr[MAXN];       // KMP 失配数组
static int  segL[MAXN], segC[MAXN]; // 栈元素：段的左端点、段长

// 求一个串的「循环最小整周期」：即最小的 p | n，使得整体循环左移 p 位不变。
// 先对单串求 KMP 失配数组，取候选周期 p = n - fail[n-1]；只有 p | n 时才是
// 真正的循环周期，否则说明没有更小的周期，答案为 n。
int min_period(int n) {
    failArr[0] = -1;
    for (int i = 1, j = -1; i <= n; i++) {
        while (j >= 0 && s[i] != s[j + 1]) j = failArr[j];
        failArr[i] = ++j;
    }
    int p = n - failArr[n];
    return (p > 0 && n % p == 0) ? p : n;
}

void solve_one(char *a, int n) {
    if (n == 1) { puts("1"); return; }

    for (int i = 1; i <= n; i++) s[i] = a[i - 1];

    // 【把 1 变多】0 占多数时取反并反转
    int zeros = 0;
    for (int i = 1; i <= n; i++) if (s[i] == '0') zeros++;
    if (zeros * 2 > n) {
        for (int i = 1; i <= n; i++) s[i] ^= 1;
        reverse(s + 1, s + n + 1);
    }

    // 【破环为链】前缀和最小处之后切开（Raney 引理）
    int cut = 0, now = 0, low = 0;
    for (int i = 1; i <= n; i++) {
        now += (s[i] == '0' ? -1 : 1);
        if (now < low) { low = now; cut = i; }
    }
    rotate(s + 1, s + cut + 1, s + n + 1);

    // 【栈模拟】从右往左扫描 01 段
    s[n + 1] = '\0';   // 哨兵：保证 i=n 时进入 "新段开始" 分支
    int top = 0, mx = 1;
    int i = n, c = 0;          // c 表示 s[i+1..i+c] 这一段的长度
    while (i >= 0) {
        if (s[i] == s[i + 1]) {
            c++;
        } else {
            // 一段（s[i+1..i+c]）刚刚结束
            if (c > 1) {
                if (s[i + 1] == '0') {
                    segL[++top] = i + 1; segC[top] = c;    // 0 段入栈
                } else {
                    // 1 段：不断吃掉栈里的 0 段
                    while (top && s[segL[top]] == '0' && c > 1) {
                        int k = segC[top], l = segL[top];
                        if (k > c) {
                            // 1 段被吃光，0 段剩下 k-c+1，左端点右移 c-1
                            int v = l - 1 - i - c;
                            if (v / 2 > mx) mx = v / 2;
                            segC[top] = k - c + 1;
                            segL[top] = l + c - 1;
                            c = 0;
                            break;
                        } else {
                            // 0 段被吃光，1 段剩 c-k+1 继续吃
                            int v = l + 2 * k - 1 - i - c;
                            if (v / 2 > mx) mx = v / 2;
                            c = c - k + 1;
                            top--;
                        }
                    }
                    if (c > 1) { segL[++top] = i + 1; segC[top] = c; }
                }
            }
            c = 1;
        }
        i--;
    }

    // 边界：最右侧长度为 1 的 1 段可能与串首的 1 段并成一段
    if (s[n - 1] == '0' && s[n] == '1' && s[1] == '1') {
        segL[++top] = n; segC[top] = 1;
    }
    if (s[2] == '0' && s[1] == '1' && s[n] == '1') {
        segL[++top] = 1; segC[top] = 1;
    }

    if (top == 0) {          // 终态里没有长度 ≥ 2 的 1 段，重建出来就是 0101… 交替串
        printf("%d\n", mx + 1);
        return;
    }

    // 【还原终态】把所有 1 段按 mx-1 反向偏移，空隙用 01 交替补齐
    for (int k = 1; k <= n; k++) s[k] = '?';
    for (int k = 1; k <= top; k++)
        for (int j = segL[k]; j < segL[k] + segC[k]; j++)
            s[(j + mx - 2) % n + 1] = '1';
    int last = 0;
    for (int k = 1; k <= n; k++) {
        if (s[k] == '1') {
            // 注意顺序：紧靠 1 段左侧的那一格要写 '0'，向左边依次 0,1,0,1
            char o = '1';
            for (int j = k - 1; j > last; j--) { o ^= 1; s[j] = o; }
            last = k;
        }
    }
    { char o = '1'; for (int j = last + 1; j <= n; j++) { o ^= 1; s[j] = o; } }

    // 【KMP】环长 = 终态最小整周期
    printf("%d\n", min_period(n) + mx - 1);
}

int main() {
    int len = (int)fread(inbuf, 1, sizeof(inbuf) - 1, stdin);
    inbuf[len] = 0;
    char *p = inbuf;
    while (*p && (*p < '0' || *p > '9')) p++;
    int T = 0;
    while (*p >= '0' && *p <= '9') T = T * 10 + (*p++ - '0');
    while (T--) {
        while (*p && *p != '0' && *p != '1') p++;
        char *st = p;
        while (*p == '0' || *p == '1') p++;
        solve_one(st, (int)(p - st));
    }
    return 0;
}
