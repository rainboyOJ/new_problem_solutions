/**
 * P3613 【深基15.例2】寄包柜
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXQ = 100005;

// 每个柜子用链表存（格子→物品）
// head[i] 指向柜子 i 的链表头
// to[cnt] 格子编号, val[cnt] 物品编号, nxt[cnt] 下一条
int head[MAXN], to[MAXQ], val[MAXQ], nxt[MAXQ];
int cnt = 0;

// 向柜子 locker 的链表头部插入 (格子,物品)
void add(int locker, int cell, int item) {
    ++cnt;
    to[cnt] = cell;
    val[cnt] = item;
    nxt[cnt] = head[locker];
    head[locker] = cnt;
}

// 查询柜子 locker 中格子 cell 上的物品
int query(int locker, int cell) {
    for (int i = head[locker]; i; i = nxt[i]) {
        if (to[i] == cell) return val[i];
    }
    return -1; // 题目保证查询都存在，不会走到这里
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    while (q--) {
        int op, locker, cell;
        scanf("%d%d%d", &op, &locker, &cell);
        if (op == 1) { // 写入
            int item;
            scanf("%d", &item);
            add(locker, cell, item);
        } else { // 查询
            printf("%d\n", query(locker, cell));
        }
    }
    return 0;
}
