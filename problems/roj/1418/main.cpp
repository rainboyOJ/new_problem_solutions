/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:15
 * update_at: 2026-10-07 15:15
 */
// main.cpp：猴子选大王。把圆圈按报数方向摊成一条队列：报数 = 队首出队，
// 没数到就排回队尾，数到就淘汰；淘汰后新的队首正好是下一轮的起点。
#include <cstdio>

typedef long long ll;

const int MAXN = 1000000 + 5;

ll n;              // 猴子总数
int x[MAXN];       // x[i]：i 号猴子作为本轮起点时要数到的次数 Xi（Xi <= 100，用 int 省内存）
int circle[MAXN];  // 循环队列：按报数方向存还在圈里的猴子编号，队首是本轮起点（编号 <= 1e6）
int head, tail;    // 队首、队尾下标
int alive_cnt;     // 队列里的猴子数，也就是圈里还剩几只

// 把猴子 v 接到队尾。队列里最多同时有 N 只猴子，容量 MAXN 的循环数组足够。
void push_monkey(int v) {
    circle[tail] = v;
    if (++tail == MAXN) tail = 0;
    ++alive_cnt;
}

// 队首猴子出队，返回它的编号。
int pop_monkey() {
    int v = circle[head];
    if (++head == MAXN) head = 0;
    --alive_cnt;
    return v;
}

// 看一眼队首猴子的编号，不出队。
int front_monkey() {
    return circle[head];
}

int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x[i]);
        push_monkey(i);  // 1..n 依次入队，队首就是 1 号猴子
    }

    ll target = x[1];  // 本轮要数到的次数，由本轮起点（队首）的 Xi 决定
    ll counted = 0;    // 本轮已经数了几只猴子

    while (alive_cnt > 1) {       // 圈里只剩一只猴子时它就是大王，n = 1 时一轮都不数
        ++counted;
        int cur = pop_monkey();   // 队首猴子报数后先出队
        if (counted == target) {  // 正好数到本轮目标：这只猴子被淘汰，不再回到圈里
            counted = 0;
            target = x[front_monkey()];  // 下一轮从它下一位开始，次数换成新队首的 Xi
        } else {
            push_monkey(cur);     // 没数到：排回队尾，等下一轮继续数
        }
    }

    printf("%d\n", front_monkey());  // 最后剩下的猴子就是大王
    return 0;
}
