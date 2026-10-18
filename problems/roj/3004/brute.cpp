/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-18 16:43
 * update_at: 2026-10-18 16:43
 */
// brute.cpp：区间最大和 —— 每次询问从 1 开始逐个试，直到前缀和超过 T。
// 时间 O(NQ)，只能过小数据，用来对拍和暴露瓶颈：每个询问都要重新扫一遍前缀。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, q;
ll sum[MAXN];

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        ll a;
        scanf("%lld", &a);
        sum[i] = sum[i - 1] + a;
    }
    while (q--) {
        ll T;
        scanf("%lld", &T);
        int k = 0;
        // 一步一步往右走，sum[k+1] 还放得下就继续走
        while (k + 1 <= n && sum[k + 1] <= T) k++;
        printf("%d\n", k);
    }
    return 0;
}
