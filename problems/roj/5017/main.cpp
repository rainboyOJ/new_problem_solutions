/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 19:48
 * update_at: 2026-10-08 19:57
 */
// main.cpp：统计方案（一本通 1681，n<=32）。
// 折半搜索（meet in the middle）+ 费马小定理求逆元：
//   左半每个子集积 x 需要右半积 y 满足 x*y ≡ c (mod p)，即 y ≡ c * x^{-1} (mod p)。
//   两半各有 2^(n/2) <= 2^16 个子集，右半每个积在左半“需求表”里二分查出现次数。
// 关于 0：题面只保证 a[i] < p，未排除 a[i] == 0，而 0 没有模逆元，不能进折半配对。
//   设 z 为 0 的个数，把 0 全部剔除后剩下 m = n - z 个非零元素：
//     含至少一个 0 的子集积恒为 0，共 (2^z - 1) * 2^m 个非空子集。
//     若 c == 0 它们全部合法，直接计入 base；若 c != 0 它们全部非法，忽略。
//   不含 0 的子集（必然可求逆）交给折半搜索处理。
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL; // 方案数的模，和题目给的质数 p 是两回事

ll n, p, c;
ll zeroCount; // 原序列里 0 的个数
ll m;         // 剔除 0 之后剩下的元素个数
ll b[40];     // b[1..m]，原序列去掉所有 0 后的非零元素

vector<ll> needList;           // 左半每个子集积 x 对应的“右半所需值” c * x^{-1} mod p
vector<pair<ll, ll> > needTab; // needList 排序去重后：(所需值, 出现次数)，供右半二分

ll ans;

// 快速幂 x^e mod mod。p 为质数时，x^(p-2) 就是 x 在 mod p 下的逆元
ll qpow(ll x, ll e, ll mod) {
    ll r = 1 % mod;
    x %= mod;
    while (e > 0) {
        if (e & 1) r = r * x % mod; // p <= 1e9 < 2^30，r * x < 2^60，long long 不会溢出
        x = x * x % mod;
        e >>= 1;
    }
    return r;
}

// 枚举左半区间 [1, r] 的每个子集，把“右半所需值”记进 needList
void dfs_left(ll dep, ll r, ll prod) {
    if (dep > r) {
        // b[] 里没有 0，p 又是质数 ⇒ prod != 0，逆元必存在
        needList.push_back(qpow(prod, p - 2, p) * c % p);
        return;
    }
    dfs_left(dep + 1, r, prod);            // 不选 b[dep]
    dfs_left(dep + 1, r, prod * b[dep] % p); // 选 b[dep]
}

// 枚举右半区间 [half+1, m] 的每个子集，在 needTab 里查这个积出现了几次
void dfs_right(ll dep, ll r, ll prod) {
    if (dep > r) {
        auto it = lower_bound(needTab.begin(), needTab.end(), make_pair(prod, 0LL));
        if (it != needTab.end() && it->first == prod) ans = (ans + it->second) % MOD;
        return;
    }
    dfs_right(dep + 1, r, prod);
    dfs_right(dep + 1, r, prod * b[dep] % p);
}

void solve() {
    if (scanf("%lld %lld %lld", &n, &p, &c) != 3) return;
    zeroCount = 0;
    m = 0;
    for (ll i = 1; i <= n; i++) {
        ll x;
        scanf("%lld", &x);
        x %= p;
        if (x == 0) zeroCount++;
        else b[++m] = x; // 0 单独计数，不放进折半数组
    }

    if (c >= p) { // 余数一定小于 p，c >= p 时一组都凑不出来
        printf("0\n");
        return;
    }

    // 含至少一个 0 的非空子集个数：(2^zeroCount - 1) * 2^m
    ll base = 0;
    if (c == 0) {
        base = (qpow(2, zeroCount, MOD) - 1 + MOD) % MOD;
        base = base * qpow(2, m, MOD) % MOD;
    }

    ll half = m / 2;
    dfs_left(1, half, 1); // 空集也参与：左半空集的积是 1

    sort(needList.begin(), needList.end());
    ll total = needList.size();
    for (ll i = 0; i < total; ) {
        ll j = i;
        while (j < total && needList[j] == needList[i]) j++;
        needTab.push_back(make_pair(needList[i], j - i));
        i = j;
    }

    dfs_right(half + 1, m, 1); // 空集也参与

    // 题面要求“至少取一个数”：c == 1 时左右都取空集也被计入了，扣掉这一种
    if (c == 1) ans = (ans - 1 + MOD) % MOD;

    ans = (ans + base) % MOD;
    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
