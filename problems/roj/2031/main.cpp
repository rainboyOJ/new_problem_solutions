/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 105;
const ll MOD = 9901;

ll n, k;         // 结点总数 N 与高度上界 K
ll m;            // 内部结点数 m = (N-1)/2，叶子数比它多 1
ll below[MAXM];  // L_{h-1}[i]：内部结点数 i、高度不超过 h-1 的家谱数
ll upto[MAXM];   // L_h[i]：内部结点数 i、高度不超过 h 的家谱数
ll nxt[MAXM];    // 抬高一层得到的中间向量 L_{h+1}

// 把高度不超过 h 的计数向量 F 卷积一次，得到高度不超过 h+1 的向量 G。
// 高度不超过 h+1 的树去掉根，左右子树高度都不超过 h，于是
// G[i] = Σ_{a+b=i-1} F[a]*F[b]，下标是内部结点数。
void lift(ll F[], ll G[]) {
    G[0] = 1; // 内部结点数 0 的那棵树（叶子）高度为 1，任何上界都包含它
    for (ll i = 1; i <= m; i++) {
        ll sum = 0;
        for (ll a = 0; a <= i - 1; a++) {
            sum = (sum + F[a] * F[i - 1 - a]) % MOD;
        }
        G[i] = sum;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 每个内部结点恰好有两个孩子，结点数必为奇数：n = m + (m+1) = 2m+1
    if (n % 2 == 0) {
        cout << 0 << "\n";
        return 0;
    }

    m = (n - 1) / 2; // 内部结点数

    // L_1：只有那片叶子，内部结点数大于 0 的树高度都超过 1
    for (ll i = 0; i <= m; i++) below[i] = 0;
    below[0] = 1;
    for (ll i = 0; i <= m; i++) upto[i] = below[i];

    // 每轮把高度上界抬高一层，共 K-1 轮；
    // 结束后 below = L_{K-1}，upto = L_K。
    for (ll h = 1; h <= k - 1; h++) {
        lift(upto, nxt);
        for (ll i = 0; i <= m; i++) {
            below[i] = upto[i];
            upto[i] = nxt[i];
        }
    }

    // 高度不超过 K 的减去高度不超过 K-1 的，剩下的正好高度为 K
    ll ans = ((upto[m] - below[m]) % MOD + MOD) % MOD;
    cout << ans << "\n";

    return 0;
}
