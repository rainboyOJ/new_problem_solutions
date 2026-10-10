/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:20
 * update_at: 2026-10-09 07:23
 */
#include <cstdio>

typedef long long ll;

// 5 个小朋友的糖果数，下标含义即编号 1..5 号，围成一圈：
// 1 号的邻居是 2 号和 5 号，5 号的邻居是 4 号和 1 号。
ll a, b, c, d, e;

// 严格按 1 -> 5 号的顺序依次操作：轮到某人时，他手里已经是前面的人分给他的
// 最新数量（不是本轮开始时的旧值）；用 share 记 floor(手中糖果 / 3) 这一份，
// 余数 c % 3 无人接手，当场吃掉，故直接丢弃。
void solve() {
    ll share;

    // 1 号：留一份，另两份给 2 号、5 号
    share = a / 3;
    a = share;
    b += share;
    e += share;

    // 2 号：留一份，另两份给 1 号、3 号
    share = b / 3;
    b = share;
    a += share;
    c += share;

    // 3 号：留一份，另两份给 2 号、4 号
    share = c / 3;
    c = share;
    b += share;
    d += share;

    // 4 号：留一份，另两份给 3 号、5 号
    share = d / 3;
    d = share;
    c += share;
    e += share;

    // 5 号：留一份，另两份给 4 号、1 号
    share = e / 3;
    e = share;
    d += share;
    a += share;

    // 题面要求「按 5 位宽度输出」：%5lld 右对齐补空格，五个数之间不加任何分隔符
    printf("%5lld%5lld%5lld%5lld%5lld\n", a, b, c, d, e);
}

int main() {
    if (scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &e) != 5) {
        return 0;
    }

    solve();

    return 0;
}
