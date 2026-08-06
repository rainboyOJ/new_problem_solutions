/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-06 22:43
 * update_at: 2026-08-06 22:43
 */

// brute.cpp：小数据暴力解，直接按题意模拟 m 次跳跃，每次暴力找出第 k 近的石头。
// 只适合 n、m 都很小的情况，用来理解题意并辅助对拍。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, k;
long long m;
long long p[MAXN]; // 石头位置，严格递增

// 从石头 start 出发，走 m 步后停在哪个石头。
int simulate(int start) {
    int cur = start;
    for (long long step = 1; step <= m; step++) {
        // 把所有石头按 (距离, 编号) 排序，找出第 k 小的距离。
        vector<pair<long long, int>> dist;
        for (int i = 1; i <= n; i++) {
            if (i == cur) continue;
            dist.push_back(make_pair(llabs(p[i] - p[cur]), i));
        }
        sort(dist.begin(), dist.end());
        // 注意：平局（多个石头距离相同且都满足条件）时，
        // 题目要求选离源头最近（编号最小）的石头，不能直接取排序后的第 k 个。
        long long d_star = dist[k - 1].first;
        cur = INT_MAX;
        for (int i = 0; i < (int)dist.size(); i++) {
            if (dist[i].first == d_star) cur = min(cur, dist[i].second);
        }
    }
    return cur;
}

int main() {
    scanf("%d%d%lld", &n, &k, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", simulate(i));
    }
    printf("\n");
    return 0;
}
