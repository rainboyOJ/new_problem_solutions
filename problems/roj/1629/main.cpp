/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:14
 * update_at: 2026-10-05 23:14
 */

// 求 sigma(n) = S 的所有 n：把 S 拆成编号段 1+p+...+p^a 之积，DFS 按质数递增枚举，
// 指数为 1 的大质数段靠「rest-1 是质数」反向收尾（Miller-Rabin 判定）。

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
typedef long long ll;

const int LIMIT = 44722; // sqrt(2e9) 上取整，指数 >= 2 的质因子 p 必有 p^2 < S
const int MAXN = 45005;

bool comp[MAXN];      // comp[i] = true 表示 i 是合数（筛表）
std::vector<ll> pri;  // 小质数表，只覆盖指数 >= 2 的情形
ll ans[100005];       // 本组询问的所有答案，最后排序输出
int cnt;              // 答案个数

// 埃氏筛出 LIMIT 以内的质数
void sieve() {
    memset(comp, 0, sizeof(comp));
    for (ll i = 2; i <= LIMIT; i++) {
        if (!comp[i]) {
            pri.push_back(i);
            for (ll j = i * i; j <= LIMIT; j += i) comp[j] = true;
        }
    }
}

// Miller-Rabin 判素：n <= 2e9 时底数 2,3,5,7 已足够（无强伪素数遗漏）
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n < (ll)MAXN && n <= LIMIT) return !comp[n];
    ll d = n - 1; // n-1 = d * 2^s
    int s = 0;
    while (!(d & 1)) { d >>= 1; s++; }
    int base[4] = {2, 3, 5, 7};
    for (int t = 0; t < 4; t++) {
        ll a = base[t];
        ll x = 1;
        // 快速幂算 a^d mod n
        ll e = d;
        while (e > 0) {
            if (e & 1) x = (__int128)x * a % n;
            a = (__int128)a * a % n;
            e >>= 1;
        }
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int i = 0; i < s - 1; i++) {
            x = (__int128)x * x % n;
            if (x == n - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

// 只能用第 start 个及之后的质数；编号段乘积还差 rest；已确定的答案部分为 cur
// 注意 n 的质因子个数不超过 9（2*3*5*7*11*13*17*19*23 > 2e9），递归深度很小
void dfs(int start, ll rest, ll cur) {
    if (rest == 1) { // 编号段全部拆完，cur 是一个答案
        ans[++cnt] = cur;
        return;
    }
    // 收尾分支：G(p,1) = 1+p = rest，即 p = rest-1 是质数时取指数 1 的大质数段
    if (rest - 1 >= pri[start] && is_prime(rest - 1)) ans[++cnt] = cur * (rest - 1);
    // 枚举指数 >= 2 的编号段：段值 1+p+...+p^a 整除 rest 才能递归
    for (int j = start; j < (int)pri.size(); j++) {
        ll p = pri[j];
        if (p * p > rest) break; // p 的指数已只能取 1，交给上面的收尾
        ll pk = p;       // pk = p^a
        ll seg = 1 + p;  // seg = 1+p+...+p^a
        while (seg <= rest) {
            if (rest % seg == 0) dfs(j + 1, rest / seg, cur * pk);
            pk *= p;
            seg += pk;
        }
    }
}

int main() {
    sieve();
    ll S;
    while (scanf("%lld", &S) == 1) {
        cnt = 0;
        dfs(0, S, 1);
        std::sort(ans + 1, ans + cnt + 1);
        printf("%d\n", cnt);
        for (int i = 1; i <= cnt; i++) printf("%lld%c", ans[i], i == cnt ? '\n' : ' ');
    }
    return 0;
}
