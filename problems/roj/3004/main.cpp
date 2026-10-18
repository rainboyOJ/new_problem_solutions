/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-18 16:43
 * update_at: 2026-10-18 16:43
 */
// main.cpp：区间最大和 —— 在线倍增（binary jump）。
// 思路：
//   1. A[i] 都是正数，前缀和 sum[i] = A[1] + ... + A[i] 严格递增，
//      所以 "sum[i] <= T" 关于 i 具有二分性：前面全可行，后面全不可行；
//   2. 于是可以用倍增跳跃：从位置 0 出发，从大到小试跳 2^i 个位置，
//      跳过去之后仍然满足 sum[pos] <= T 才真的跳，最后停下的位置就是最大的 k；
//   3. 每个询问 O(log N)，读到一个回答一个，不需要等后面的询问，所以是在线的。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, q;
int maxk;         // 最大的 i，使得 2^i <= n，跳跃从 2^maxk 开始试
ll sum[MAXN];     // sum[i] = A[1] + ... + A[i]，sum[0] = 0；值域 1e5 * 1e9，要用 ll

// 得到最大的 k，使得 2^k <= n
int get_max_k(int n)
{
    int k = 0;
    while ((1LL << (k + 1)) <= n) k++;
    return k;
}

// 检查跳到位置 pos 之后是否仍然可行（前缀和不超过 T）
bool check(int pos, ll T)
{
    return pos <= n && sum[pos] <= T;
}

// 从位置 0 开始向右跳，求最后一个满足 sum[pos] <= T 的位置
int jump(ll T)
{
    int x = 0; // 当前停留位置，起点是 0：sum[0] = 0 一定可行
    for (int i = maxk; i >= 0; i--) {
        int len = (1 << i); // 本轮尝试的跳跃长度是 2^i
        int pos = x + len;  // 跳过去之后的位置
        if (check(pos, T)) {
            x = pos;        // 不越界且不超过 T 才真的跳
        }
    }
    return x;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        ll a;
        scanf("%lld", &a);
        sum[i] = sum[i - 1] + a; // 前缀和
    }

    maxk = get_max_k(n);

    while (q--) {
        ll T;
        scanf("%lld", &T);
        printf("%d\n", jump(T)); // 读完一个询问马上回答
    }
    return 0;
}
