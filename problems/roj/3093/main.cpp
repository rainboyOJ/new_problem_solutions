/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:35
 * update_at: 2026-10-06 18:35
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const ll MOD = 1000000009;  // 题目要求的模数，注意不是常见的 1e9+7
const int MAXN = 100005;    // n 的最大规模

int p[MAXN];    // p[i] 表示排列第 i 个位置上的数值（下标从 1 开始）
int vis[MAXN];  // vis[i] 标记位置 i 是否已经在轮换分解中被走过
ll fact[MAXN];  // fact[i] = i! mod MOD

// 快速幂：计算 base^exp mod MOD。
ll mod_pow(ll base, ll exp) {
    ll res = 1 % MOD;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// 预处理阶乘，供 m! 和 (c-1)! 使用。
void init_fact() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
}

void solve() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &p[i]);
            vis[i] = 0;
        }

        // 沿「位置 i -> 位置 p[i]」走，把排列分解成若干轮换。
        // 设轮换个数为 k，则最少交换次数 m = n - k；
        // 每个长度 c 的非平凡轮换贡献 c^(c-2) * ((c-1)!)^(-1)（Dénes 定理）。
        int cycle_count = 0;
        ll ans = 1;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            int len = 0;
            int j = i;
            while (!vis[j]) {
                vis[j] = 1;
                j = p[j];
                len++;
            }
            cycle_count++;
            if (len > 1) {
                ans = ans * mod_pow(len, len - 2) % MOD;              // c^(c-2)
                ans = ans * mod_pow(fact[len - 1], MOD - 2) % MOD;    // 除以 (c-1)!
            }
        }

        ll m = n - cycle_count;      // 最少交换次数
        ans = ans * fact[m] % MOD;   // 再乘上 m 次操作的穿插方案数 m!
        printf("%lld\n", ans);
    }
}

int main() {
    init_fact();
    solve();
    return 0;
}
