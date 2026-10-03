/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:30
 */
// P9719 [EC Final 2022] Minimum Suffix
// 题意：给每个前缀的最小后缀起点 p_i，还原字典序最小的串 s（字符用正整数表示），无解输出 -1。
// 核心：p_i 就是前缀 i 的 Lyndon 分解中最后一个 Lyndon 串的起点。
//       于是从后往前把整个串切成 Lyndon 串，再在块内模拟 Duval，最后从右往左贪心。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000005;

int n;
int p[MAXN];              // 输入的 p_i
int pre[MAXN];            // Duval 中的 j 指针，s[i] 由 s[pre[i]] 推出
unsigned char val[MAXN];  // 1：s[i] = s[pre[i]] + 1（s_j < s_k）；0：s[i] = s[pre[i]]（s_j = s_k）
int s[MAXN];              // 答案串，字符从 0 开始编号
int nb[MAXN];             // 右边相邻 Lyndon 串（next block）的字符

// 手写快读，输入输出可达 3e6 规模
namespace fastio {
const int IBUF = 1 << 22;
char ibuf[IBUF];
int iidx, ilen;

inline int gc() {
    if (iidx == ilen) {
        ilen = (int)fread(ibuf, 1, IBUF, stdin);
        iidx = 0;
        if (ilen <= 0) return -1;
    }
    return (unsigned char)ibuf[iidx++];
}

inline int readInt() {
    int c = gc();
    while (c < '0' || c > '9') {
        if (c == -1) return -1;
        c = gc();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

const int OBUF = 1 << 22;
char obuf[OBUF];
int oidx;

inline void flushOut() {
    if (oidx) {
        fwrite(obuf, 1, oidx, stdout);
        oidx = 0;
    }
}

inline void putChar(char c) {
    if (oidx == OBUF) flushOut();
    obuf[oidx++] = c;
}

inline void writeInt(int x) {
    if (x == 0) {
        putChar('0');
        return;
    }
    if (x < 0) {
        putChar('-');
        x = -x;
    }
    char tmp[16];
    int t = 0;
    while (x) {
        tmp[t++] = char('0' + x % 10);
        x /= 10;
    }
    while (t) putChar(tmp[--t]);
}
}  // namespace fastio

// 在单个 Lyndon 串 [l, r] 内模拟 Duval 算法。
// 求出每个位置的 j 指针 pre[i] 以及 s_pre 与 s_i 的关系 val[i]。
// 返回 false 表示这个块无法由 p 解释，整组数据无解。
bool prepare_block(int l, int r) {
    val[l] = 1;  // 块首字符是自由变量，val 只作占位

    // 块内每个位置的最小后缀都必须落在块内
    for (int i = l; i <= r; ++i) {
        if (p[i] < l) return false;
    }

    int len = 1;  // 当前近似 Lyndon 串的周期长度
    for (int i = l + 1; i <= r; ++i) {
        pre[i] = i - len;
        if (p[i] == l) {
            // s_j < s_k，从 l 到 i 合并成一个新的 Lyndon 串
            val[i] = 1;
            len = i - l + 1;
        } else if (i - p[i] == (i - len) - p[i - len]) {
            // s_j == s_k，最小后缀起点整体平移 len
            val[i] = 0;
        } else {
            return false;  // 出现第三种情况，无解
        }
    }
    return true;
}

// 构造块 [l, r] 的取值，要求它字典序 >= 右边相邻块 nb[1..m] 且尽量小。
void build_block(int l, int r, int m) {
    int len = r - l + 1;
    int gt = 0;  // 当前块是否已经确定大于右边块
    s[l] = (m >= 1) ? nb[1] : 0;

    for (int i = l + 1; i <= r; ++i) {
        s[i] = s[pre[i]] + val[i];
        int t = i - l + 1;
        int c = (t <= m) ? nb[t] : 0;  // 右边块第 t 个字符，越界视为最小字符 0
        if (s[i] > c) {
            gt = 1;
        }
        if (!gt && s[i] < c) {
            if (val[i]) {
                // 这一位自由，直接抬到与右边块相等
                s[i] = c;
            } else {
                // 这一位必须等于 s[pre[i]]，只能把前面最近的自由位加一
                int now = i;
                while (val[now] != 1) --now;
                i = now;  // 从 now 之后重新推一遍
                s[now]++;
                gt = 1;
            }
        }
    }

    if (!gt && len < m) {
        // 整块是右边块的前缀，字典序更小，抬高最后一个自由位
        int now = r;
        while (val[now] != 1) --now;
        s[now]++;
        for (int i = now + 1; i <= r; ++i) s[i] = s[pre[i]] + val[i];
    }
}

// 处理一组数据，返回是否存在解
bool solve_case() {
    n = fastio::readInt();
    for (int i = 1; i <= n; ++i) p[i] = fastio::readInt();

    // 从后往前切分 Lyndon 串：block = [l, r]，其中 l = p[r]
    int r = n;
    int m = 0;  // 右边相邻块的串长
    while (r >= 1) {
        int l = p[r];
        if (!prepare_block(l, r)) return false;

        build_block(l, r, m);

        // 当前块成为下一轮的“右边块”
        m = r - l + 1;
        for (int i = l; i <= r; ++i) nb[i - l + 1] = s[i];
        r = l - 1;
    }
    return true;
}

int main() {
    int T = fastio::readInt();
    while (T--) {
        if (!solve_case()) {
            fastio::putChar('-');
            fastio::putChar('1');
            fastio::putChar('\n');
        } else {
            for (int i = 1; i <= n; ++i) {
                fastio::writeInt(s[i] + 1);
                fastio::putChar(i == n ? '\n' : ' ');
            }
        }
    }
    fastio::flushOut();
    return 0;
}
