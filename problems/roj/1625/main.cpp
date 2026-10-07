/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:10
 * update_at: 2026-10-05 23:10
 */

#include <cstdio>

typedef long long ll;

const int PNUM = 10; // n <= 2*10^9，前 10 个质数连乘 6469693230 已超界，最多用到第 10 个质数

// 前若干个质数：反素数的质因子必由连续前缀质数构成
ll pri[PNUM + 1] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

ll n;       // 题目给定的上界
ll best_num = 1;  // 当前最优反素数（约数最多，同约数个数时数值最小）
ll best_divs = 1; // 当前最优反素数的约数个数

// 按序枚举第 idx 个质数的指数 exp：1..max_exp（指数单调不增的剪枝）
// num：当前累积的数；divs：当前约数个数（各 (指数+1) 的乘积）
void dfs(ll idx, ll max_exp, ll num, ll divs) {
    // 每个节点都是一个候选数：约数更多者优先，约数相同取数值更小者
    if (divs > best_divs || (divs == best_divs && num < best_num)) {
        best_num = num;
        best_divs = divs;
    }

    if (idx > PNUM) return; // 质数用尽

    ll cur = num;
    // 这一层在选择第 idx 个质数的指数，指数不能超过上一层的 max_exp
    for (ll e = 1; e <= max_exp; ++e) {
        cur *= pri[idx];
        if (cur > n) break; // 超过 n，再乘只会更大，剪枝回溯
        dfs(idx + 1, e, cur, divs * (e + 1));
    }
}

int main() {
    scanf("%lld", &n);
    // 初始约数个数上界 31：2^31 > 2*10^9，质数 2 的指数最多 30
    dfs(1, 31, 1, 1);
    printf("%lld\n", best_num);
    return 0;
}
