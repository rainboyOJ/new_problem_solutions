/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P2240 部分背包问题 */
/* 按单位价值从高到低排序，能整堆拿就整堆拿，装不下时拿一部分然后结束。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, capacity;
// 每堆金币：重量、价值、单位价值
int w[MAXN], v[MAXN];
double r[MAXN]; // 单位价值 = v / w
int idx[MAXN];  // 排序用的索引

// 按单位价值降序排列
bool cmp(int a, int b) {
    return r[a] > r[b];
}

int main() {
    cin >> n >> capacity;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        r[i] = (double)v[i] / w[i];
        idx[i] = i;
    }

    // 按单位价值降序排序
    sort(idx + 1, idx + n + 1, cmp);

    double ans = 0.0;
    int remain = capacity;
    for (int i = 1; i <= n && remain > 0; i++) {
        int id = idx[i];
        // 能拿多少拿多少
        int take = min(remain, w[id]);
        ans += take * r[id];
        remain -= take;
    }

    printf("%.2f\n", ans);
    return 0;
}
