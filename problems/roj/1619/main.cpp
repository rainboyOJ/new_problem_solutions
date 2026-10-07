/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:02
 */

// 分段筛（区间筛）模板题：R 可达 2^31，但 R-L <= 10^6。
// 先筛出 [2, sqrt(R)] 内的小质数，再用它们划掉 [L,R] 中的合数，
// 剩下的就是区间内的全部质数，线性扫描相邻差取最小/最大即可。

#include <cstdio>
#include <cstring>

typedef long long ll;

const int BASE = 46341;      // sqrt(2^31) < 46341，小质数筛到这个上界就够
const int MAXN = 1000005;    // 区间长度 R-L+1 最大为 10^6+1

bool is_comp[BASE + 1];      // 埃氏筛的标记数组：is_comp[i]=1 表示 i 是合数
ll base_primes[5000];        // [2, 46341] 内的小质数约 4800 个（π(46341)=4792）
ll cnt_base;                 // 小质数个数

bool seg_comp[MAXN];         // seg_comp[i]=1 表示数字 L+i 是合数

// 埃氏筛预处理 [2, BASE] 内的小质数
void sieve_base() {
    memset(is_comp, 0, sizeof(is_comp));
    cnt_base = 0;
    for (ll i = 2; i <= BASE; i++) {
        if (!is_comp[i]) {
            base_primes[++cnt_base] = i; // 下标从 1 开始存
            for (ll j = i * i; j <= BASE; j += i) is_comp[j] = 1;
        }
    }
}

// 用小质数表对 [L, R] 做分段筛，划掉区间内所有合数
void segment_sieve(ll L, ll R) {
    // 初始时假定区间内每个数都是质数候选（下标 i 对应数字 L+i）
    memset(seg_comp, 0, sizeof(seg_comp));
    for (ll k = 1; k <= cnt_base; k++) {
        ll p = base_primes[k];
        if (p * p > R) break; // p^2 > R 时 p 无法在区间内构成任何合数，后面只会更大

        // 第一个要划掉的倍数：不小于 L 的最小 p 倍数，但不能低于 p^2
        // （p^2 以下的倍数已被更小的质数划过；p >= L 时取 p^2 可避免误划质数 p 自己）
        ll start = (L + p - 1) / p * p;
        if (start < p * p) start = p * p;

        for (ll j = start; j <= R; j += p) seg_comp[j - L] = 1;
    }

    // 数字 1 不是质数，但它不会被任何小质数划掉，需要单独排除
    if (L == 1) seg_comp[0] = 1;
}

// 对区间内剩下的质数线性扫描，输出相邻差最小/最大的数对
void solve(ll L, ll R) {
    segment_sieve(L, R);

    // prev 记录上一个质数；diff 用 -1 区分"还没有质数对"
    ll prev = 0, diff_min = -1, diff_max = -1;
    ll ans_a1 = 0, ans_b1 = 0, ans_a2 = 0, ans_b2 = 0;

    for (ll i = L; i <= R; i++) {
        if (seg_comp[i - L]) continue; // 合数跳过
        if (prev == 0) { prev = i; continue; }
        ll diff = i - prev;
        if (diff_min == -1 || diff < diff_min) {
            // 并列时取更靠前的：只在严格更小时更新
            diff_min = diff;
            ans_a1 = prev; ans_b1 = i;
        }
        if (diff_max == -1 || diff > diff_max) {
            // 并列时取更靠前的：只在严格更大时更新
            diff_max = diff;
            ans_a2 = prev; ans_b2 = i;
        }
        prev = i;
    }

    if (diff_min == -1)
        printf("There are no adjacent primes.\n");
    else
        printf("%lld,%lld are closest, %lld,%lld are most distant.\n",
               ans_a1, ans_b1, ans_a2, ans_b2);
}

int main() {
    sieve_base();
    ll L, R;
    while (scanf("%lld %lld", &L, &R) == 2) {
        solve(L, R);
    }
    return 0;
}
