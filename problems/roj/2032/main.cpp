/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:51
 * update_at: 2026-10-06 09:51
 */

// main.cpp：和为零（USACO zerosum）
// 做法：每对相邻数字之间填 '+', '-', ' ' 三种符号，共 3^(n-1) 种方案，
// 全部枚举并求值，输出结果为 0 的表达式。
// 按 ' ' < '+' < '-' 的顺序从前往后枚举，正好就是题目要求的 ASCII 输出顺序。

#include <cstdio>

typedef long long ll;

const int MAXN = 15;

ll n;                              // 数列长度
char sym[MAXN];                    // sym[i]：第 i 个空隙填入的符号
char buf[2 * MAXN + 5];            // 拼接出的表达式字符串
ll len;                            // buf 的当前长度

char order[3] = {' ', '+', '-'};   // 三种符号按 ASCII 从小到大排列

// 根据当前 sym[] 拼出完整表达式，空格直接跳过（表示把相邻数字拼成一个多位数）
void build() {
    len = 0;
    for (ll i = 1; i <= n; ++i) {
        buf[len] = '0' + i;
        ++len;
        if (i < n) {
            buf[len] = sym[i];
            ++len;
        }
    }
    buf[len] = '\0';
}

// 扫描表达式求值：先累加当前项，遇到 + / - 时把当前项结算进总和
ll calc() {
    ll total = 0;
    ll cur = 0;    // 当前项正在拼接的数值
    ll sign = 1;   // 当前项的符号，第一项默认为正
    for (ll i = 0; i < len; ++i) {
        char c = buf[i];
        if (c == '+') {
            total += sign * cur;
            cur = 0;
            sign = 1;
        } else if (c == '-') {
            total += sign * cur;
            cur = 0;
            sign = -1;
        } else if (c == ' ') {
            continue;  // 空格表示拼接，忽略即可
        } else {
            cur = cur * 10 + (c - '0');
        }
    }
    total += sign * cur;
    return total;
}

// 第 dep 个空隙选择符号，选完 n-1 个后检查表达式是否等于 0
void dfs(ll dep) {
    if (dep == n) {
        build();
        if (calc() == 0)
            printf("%s\n", buf);
        return;
    }
    for (int k = 0; k < 3; ++k) {
        sym[dep] = order[k];
        dfs(dep + 1);
    }
}

int main() {
    scanf("%lld", &n);
    dfs(1);
    return 0;
}
