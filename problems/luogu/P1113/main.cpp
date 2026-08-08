/**
 * P1113 杂务
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int len[MAXN];     // 每个任务耗时
int finish[MAXN];  // 最早完成时间
int n, ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int id, dur, pre;
        scanf("%d%d", &id, &dur);
        len[id] = dur;
        int earliest = 0;
        // 读入所有前置任务
        while (scanf("%d", &pre) && pre)
            earliest = max(earliest, finish[pre]);
        finish[id] = earliest + dur;
        ans = max(ans, finish[id]);
    }
    printf("%d\n", ans);
    return 0;
}
