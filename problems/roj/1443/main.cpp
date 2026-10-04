/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:40
 * update_at: 2026-10-05 01:41
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXD = 32;      // 答案链的最大长度；n 在本题范围内远小于 2^30
const int MAXCAND = MAXD * MAXD;

ll n;                     // 当前询问的 n
ll chain[MAXD];           // 迭代加深时正在构造的链，chain[0] = 1，严格递增
ll best[MAXD];            // 搜到的最短链
ll best_len;              // 最短链最后一项的下标，即最优步数 m
ll cand[MAXD][MAXCAND];   // cand[step] 保存该层链里两两相加得到的候选值，按层存放避免递归互相覆盖
int cand_cnt[MAXD];       // cand_cnt[step] 是 cand[step] 里的候选个数

// 返回 n 的步数下界：每步末值最多翻倍，所以至少要 log2(n) 步。
ll depth_lower_bound(ll x)
{
    ll d = 0;
    ll v = 1;
    while (v < x) {
        v *= 2;
        d++;
    }
    return d;
}

// 上取整的 a / b。
ll ceil_div(ll a, ll b)
{
    return (a + b - 1) / b;
}

// dfs(step, remain)：当前链最后一项下标是 step，还剩 remain 步可用。
// 能在 remain 步内走到 n 就保存整条链并返回 true，否则返回 false。
bool dfs(ll step, ll remain)
{
    ll last = chain[step];
    if (last == n) {
        best_len = step;
        for (ll i = 0; i <= step; i++) {
            best[i] = chain[i];
        }
        return true;
    }

    // 剪枝一：末值每步最多翻倍，remain 步后也够不到 n。
    if (last << remain < n) {
        return false;
    }

    // 候选新值只能由链中两数相加得到（下标可相同，即翻倍），收集后从大到小尝试。
    cand_cnt[step] = 0;
    for (ll i = 0; i <= step; i++) {
        for (ll j = 0; j <= i; j++) {
            cand[step][cand_cnt[step]] = chain[i] + chain[j];
            cand_cnt[step]++;
        }
    }
    sort(cand[step], cand[step] + cand_cnt[step], greater<ll>());

    // 剪枝二：新值 v 之后还剩 remain-1 步，必须满足 v * 2^(remain-1) >= n；
    // 同时链严格递增，v 至少要大于 last。
    ll lower = ceil_div(n, 1LL << (remain - 1));
    if (lower < last + 1) {
        lower = last + 1;
    }

    for (int k = 0; k < cand_cnt[step]; k++) {
        ll v = cand[step][k];
        if (v < lower) {
            break;                       // 候选从大到小排列，后面只会更小
        }
        if (v > n) {
            continue;
        }
        if (k > 0 && v == cand[step][k - 1]) {
            continue;                    // 同一候选值只试一次
        }
        chain[step + 1] = v;
        if (dfs(step + 1, remain - 1)) {
            return true;
        }
    }
    return false;
}

int main()
{
    while (scanf("%lld", &n) == 1) {
        if (n == 0) {
            break;
        }

        chain[0] = 1;
        // 迭代加深：从步数下界开始逐层 +1，第一条搜到的链就是最短链。
        for (ll depth = depth_lower_bound(n); depth <= 30; depth++) {
            if (dfs(0, depth)) {
                break;
            }
        }

        for (ll i = 0; i <= best_len; i++) {
            if (i > 0) {
                printf(" ");
            }
            printf("%lld", best[i]);
        }
        printf("\n");
    }
    return 0;
}
