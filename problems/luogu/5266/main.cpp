/**
 * P5266 【深基17.例6】学籍管理
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXQ = 100005;
const int MOD = 100003;

// 哈希表（链地址法）：名字→成绩
// 名字用 base-27 编码成 unsigned long long
struct Entry {
    unsigned long long key;
    int score;
    int next;
} tbl[MAXQ];
int head[MOD], cnt;

unsigned long long encode(const char *s) {
    unsigned long long h = 0;
    for (int i = 0; s[i]; ++i)
        h = h * 27 + (s[i] - 'a' + 1);
    return h;
}

void set_score(unsigned long long key, int score) {
    int idx = key % MOD;
    for (int i = head[idx]; i; i = tbl[i].next) {
        if (tbl[i].key == key) { tbl[i].score = score; return; }
    }
    ++cnt;
    tbl[cnt].key = key;
    tbl[cnt].score = score;
    tbl[cnt].next = head[idx];
    head[idx] = cnt;
}

int get_score(unsigned long long key) {
    int idx = key % MOD;
    for (int i = head[idx]; i; i = tbl[i].next)
        if (tbl[i].key == key) return tbl[i].score;
    return -1;
}

void erase_key(unsigned long long key) {
    int idx = key % MOD;
    for (int i = head[idx]; i; i = tbl[i].next) {
        if (tbl[i].key == key) { tbl[i].score = -1; return; }
    }
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            char name[15];
            int score;
            scanf("%s%d", name, &score);
            set_score(encode(name), score);
            puts("OK");
        } else if (op == 2) {
            char name[15];
            scanf("%s", name);
            int s = get_score(encode(name));
            if (s == -1) puts("Not found");
            else printf("%d\n", s);
        } else if (op == 3) {
            char name[15];
            scanf("%s", name);
            unsigned long long key = encode(name);
            if (get_score(key) == -1) puts("Not found");
            else { erase_key(key); puts("Deleted successfully"); }
        } else {
            printf("%d\n", cnt);
        }
    }
    return 0;
}
