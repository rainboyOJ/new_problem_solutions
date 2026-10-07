/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:13
 * update_at: 2026-10-06 15:13
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 300005;

ll pre[MAXN];   // pre[i] = a[1] + ... + a[i]，前缀和，pre[0] = 0
int q[MAXN];    // 单调队列，存前缀和下标；队头到队尾 pre 值严格递增
int head, tail; // 队列区间为 [head, tail)

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        ll x;
        scanf("%lld", &x);
        pre[i] = pre[i - 1] + x;
    }

    ll ans = pre[1] - pre[0]; // 子段长度至少为 1，先用 a[1] 兜底
    head = 0;
    tail = 0;
    q[tail++] = 0; // 初始把 i = 0（pre[0] = 0）放进窗口

    for (int r = 1; r <= n; r++) {
        // 队头下标太老，对应子段长度超过 m，弹出
        while (head < tail && q[head] < r - m) {
            head++;
        }
        // 队头即窗口 [r-m, r-1] 内最小前缀和的下标
        ll cur = pre[r] - pre[q[head]];
        if (cur > ans) {
            ans = cur;
        }
        // 队尾那些前缀和不比 pre[r] 小、又更早过期的下标再也没用，弹出
        while (head < tail && pre[q[tail - 1]] >= pre[r]) {
            tail--;
        }
        q[tail++] = r;
    }

    printf("%lld\n", ans);
    return 0;
}
