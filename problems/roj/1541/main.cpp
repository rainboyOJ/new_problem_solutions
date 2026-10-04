/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:11
 * update_at: 2026-10-05 07:11
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;   // 数列长度上限
const int LOG = 17;        // 2^17 > 1e5，层数足够覆盖所有区间长度

int n, m;
int a[MAXN];               // 原数列，1-based
int st[LOG][MAXN];         // st[k][i]：从 i 开始、长度 2^k 的区间最大值
int logs[MAXN];            // logs[x] = floor(log2(x))，预处理避免查询时算浮点对数

// 求 floor(log2(x))（x >= 1），只用在建表前确定层数
int log2_floor(int x) {
    int res = 0;
    while ((1 << (res + 1)) <= x) res++;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    // 建表：第 0 层是长度 1 的区间，就是原数列本身
    int K = log2_floor(n); // 最大有用的层号，2^K <= n < 2^(K+1)
    for (int i = 1; i <= n; i++) st[0][i] = a[i];
    // 长度 2^k 的区间由两个长度 2^(k-1) 的半段取 max 拼成
    for (int k = 1; k <= K; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);

    // logs 递推：x 的一半的对数再加一，线性预处理，查询 O(1)
    logs[1] = 0;
    for (int x = 2; x <= n; x++) logs[x] = logs[x >> 1] + 1;

    // 每条询问：两段等长 2^k 区间允许重叠地覆盖 [l, r]
    // max 幂等，重叠部分重复取不影响答案
    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int k = logs[r - l + 1]; // 不超过区间长度的最大 2 的幂
        printf("%d\n", max(st[k][l], st[k][r - (1 << k) + 1]));
    }
    return 0;
}
