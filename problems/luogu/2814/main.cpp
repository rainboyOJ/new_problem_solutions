/**
 * P2814 家谱
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int MOD = 50021;

// 哈希表：名字 → 父结点指针（编号）
struct Entry {
    char name[12]; // 原名字，用于输出
    int parent;    // 父结点在 tbl 中的下标，自己指向自己即为根
    int next;      // 哈希链表
} tbl[MAXN];
int head[MOD], cnt;

// 简单的字符串哈希
int hash_str(const char *s) {
    unsigned int h = 0;
    for (int i = 0; s[i]; ++i)
        h = h * 131 + s[i];
    return h % MOD;
}

int get_or_create(const char *s) {
    int hv = hash_str(s);
    for (int i = head[hv]; i; i = tbl[i].next)
        if (!strcmp(tbl[i].name, s)) return i;
    ++cnt;
    strcpy(tbl[cnt].name, s);
    tbl[cnt].parent = cnt; // 初始指向自己
    tbl[cnt].next = head[hv];
    head[hv] = cnt;
    return cnt;
}

// 找祖先（带路径压缩）
int find(int x) {
    if (tbl[x].parent != x)
        tbl[x].parent = find(tbl[x].parent);
    return tbl[x].parent;
}

int main() {
    char line[20];
    int cur = 0;
    while (scanf("%s", line) == 1) {
        if (line[0] == '$') break;
        int id = get_or_create(line + 1);
        if (line[0] == '#') {
            cur = id;
        } else if (line[0] == '+') {
            tbl[id].parent = cur;
        } else { // '?'
            int root = find(id);
            printf("%s %s\n", line + 1, tbl[root].name);
        }
    }
    return 0;
}
