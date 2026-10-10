/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 铺地砖：轮廓线 DP，逐行推进，状态是本行被上方横牌占住的列集合。
#include <cstdio>
#include <cstring>

typedef long long ll;

const ll MAXN = 13;
const ll MAXS = 1 << MAXN;

ll n, m;
ll memo[MAXN][MAXS];   // g[j][s] 的记忆化
char vis[MAXN][MAXS];

ll dfs_row(ll j, ll pos, ll cur, ll s);

// 处理第 j+1 行：进入时该行已被占列为 s，返回本行填完后传给下一行的伸出列集合的方案数
ll g(ll j, ll s) {
    if (j == m) return (s == 0) ? 1 : 0;
    if (vis[j][s]) return memo[j][s];
    ll res = dfs_row(j, 0, 0, s);
    vis[j][s] = 1;
    memo[j][s] = res;
    return res;
}

// 逐格填第 j+1 行，cur 为本行向下伸出的列集合
ll dfs_row(ll j, ll pos, ll cur, ll s) {
    if (pos == n) return g(j + 1, cur);
    ll b = 1LL << pos;
    if (s & b) return dfs_row(j, pos + 1, cur, s); // 该格已被上方横牌占据
    ll res = dfs_row(j, pos + 1, cur | b, s);      // 竖牌：向下一行伸出
    if (pos + 1 < n && !(s & (b << 1))) {          // 横牌：占 (pos,pos+1)，不伸出
        res += dfs_row(j, pos + 2, cur, s);
    }
    return res;
}

int main() {
    ll a, b;
    while (scanf("%lld %lld", &a, &b) == 2) {
        if (a == 0 && b == 0) break;
        n = a;
        m = b;
        memset(vis, 0, sizeof(vis)); // 记忆化缓存与 m 有关，每个用例必须清空
        printf("%lld\n", g(0, 0));
    }
    return 0;
}
