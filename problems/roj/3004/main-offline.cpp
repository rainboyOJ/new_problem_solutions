/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-18 16:43
 * update_at: 2026-10-18 16:43
 */
// main-offline.cpp：区间最大和 —— 离线做法：把询问按 T 排序 + 双指针。
// 思路：
//   1. 前缀和 sum[i] 严格递增，所以对固定的 T，答案 k 就是"sum[k] <= T"的最后一个 k；
//   2. T 越大答案 k 越大，于是把全部询问按 T 从小到大排序，
//      维护一个只会向右走的指针 k，边加边回答：sum[k+1] <= T 就一直 k++；
//   3. 排完序后每个位置最多被 k 扫过一次，总时间 O(N + Q log Q)，
//      但要求先读入所有询问再统一回答，因此是离线的。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, q;
ll sum[MAXN];     // sum[i] = A[1] + ... + A[i]，sum[0] = 0
int ans[MAXN];    // ans[id]：第 id 个询问（按读入顺序编号）的答案

struct Query {
    ll t;         // 询问值 T
    int id;       // 原始读入顺序，用于把答案放回原位
};
Query query[MAXN];

// 按 T 从小到大排序：排序后答案 k 单调不减
bool cmp(Query a, Query b)
{
    return a.t < b.t;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        ll a;
        scanf("%lld", &a);
        sum[i] = sum[i - 1] + a;
    }

    for (int i = 0; i < q; i++) {
        scanf("%lld", &query[i].t);
        query[i].id = i;
    }

    sort(query, query + q, cmp);

    int k = 0; // 双指针：当前已验证 sum[k] <= 当前 T 的最大位置
    for (int i = 0; i < q; i++) {
        // T 递增，k 只向右走，所以这里整体是线性的
        while (k + 1 <= n && sum[k + 1] <= query[i].t) k++;
        ans[query[i].id] = k;
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i]); // 按原始顺序输出
    }
    return 0;
}
