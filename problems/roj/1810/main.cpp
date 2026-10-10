/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:53
 * update_at: 2026-10-08 04:53
 */
// 登山（roj 1810）
//
// 题意：从 (0,0) 走到 (N,N)，每步只能向右 (x+1,y) 或向上 (x,y+1)；
//   站在山脊 (x,x) 上时不允许向上走，等价于路径全程满足 x >= y（不越过直线 y = x）。
//   网格中有 C 个不可走的坑，求合法路径数 mod 1e9+7。
//   数据范围：N <= 1e5，C <= 1000，坑点满足 X >= Y，(0,0) 与 (N,N) 一定不是坑。
//
// 算法（O(N + C^2)）：
//   1) 反射原理求两点间"不越过 y = x"的路径数（见 ridge_paths）。
//   2) 按"第一次踩到的坑"对路径容斥：first_hit[i] = 走到坑 i 且 i 是首个被踩到的坑的方案数，
//      最终答案 = path((0,0)->(N,N)) - sum first_hit[i] * path(坑 i -> (N,N))。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;   // 取模模数
const int MAXC = 1005;         // 坑的个数上限 C <= 1000
const int MAXF = 200005;       // 阶乘表长度上限：一条路径最多走 2N 步，2N <= 2e5

struct Point {                 // 一个坑的坐标
    ll x;
    ll y;
};

Point hole[MAXC];              // 所有坑，按 (x,y) 升序排列后使用
ll first_hit[MAXC];            // first_hit[i] = 走到 hole[i] 且 hole[i] 是首个被踩到的坑的路径数

ll fac[MAXF];                  // fac[i] = i!
ll inv_fac[MAXF];              // inv_fac[i] = (i!)^(-1) mod MOD

// 快速幂：求 a^b mod MOD
ll power_mod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 坑的排序规则：先按横坐标 x，再按纵坐标 y
bool cmp_hole(const Point &a, const Point &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// 组合数 C(total, pick) mod MOD，下标越界一律返回 0
ll comb(ll total, ll pick) {
    if (pick < 0 || pick > total || total < 0) return 0;
    return fac[total] * inv_fac[pick] % MOD * inv_fac[total - pick] % MOD;
}

// 从 (sx,sy) 走到 (tx,ty)、全程满足 x >= y 的路径数
// 总数 C(dx+dy, dx)；越过直线 y = x+1 的非法路径由反射原理与"终点关于 y=x+1 的对称点
// (ty-1, tx+1)"一一对应，故非法数为 C(dx+dy, ty-sx-1)（组合下标非法时该项为 0）。
ll ridge_paths(ll sx, ll sy, ll tx, ll ty) {
    if (tx < sx || ty < sy) return 0;                    // 终点在起点左下方，不可达
    ll total = (tx - sx) + (ty - sy);                    // 总步数
    ll all = comb(total, tx - sx);                       // 不做界限约束的路径数
    ll bad = (ty > sx) ? comb(total, ty - sx - 1) : 0;   // 反射项；ty <= sx 时必无非法路径
    return (all - bad + MOD) % MOD;
}

// 预处理 0..limit 的阶乘与阶乘逆元，使任意组合数 O(1) 得出
void build_factorials(int limit) {
    fac[0] = 1;
    for (int i = 1; i <= limit; i++) fac[i] = fac[i - 1] * (ll)i % MOD;
    inv_fac[limit] = power_mod(fac[limit], MOD - 2);
    for (int i = limit - 1; i >= 0; i--) inv_fac[i] = inv_fac[i + 1] * (ll)(i + 1) % MOD;
}

// 按 (x,y) 升序排坑（保证坑之间只可能从前往后走，DP 无环），并去掉重复点
int sort_and_unique_holes(int c) {
    sort(hole, hole + c, cmp_hole);
    int m = 0;
    for (int i = 0; i < c; i++) {
        if (m > 0 && hole[m - 1].x == hole[i].x && hole[m - 1].y == hole[i].y) continue;
        hole[m++] = hole[i];
    }
    return m;
}

// 按"首个被踩到的坑"容斥：返回从 (0,0) 到 (N,N) 且不经过任何坑的合法路径数
ll count_paths(ll n, int m) {
    for (int i = 0; i < m; i++) {
        ll ways = ridge_paths(0, 0, hole[i].x, hole[i].y);   // 先算无视其他坑的方案数
        for (int j = 0; j < i; j++) {
            if (hole[j].y > hole[i].y) continue;             // 坑 j 不可能出现在通往坑 i 的路上
            ll tail = ridge_paths(hole[j].x, hole[j].y, hole[i].x, hole[i].y);
            ways = (ways - first_hit[j] * tail) % MOD;       // 扣除"首个坑是 j、随后走到 i"的方案
        }
        first_hit[i] = (ways % MOD + MOD) % MOD;
    }

    ll ans = ridge_paths(0, 0, n, n);
    for (int i = 0; i < m; i++) {
        ll tail = ridge_paths(hole[i].x, hole[i].y, n, n);
        ans = (ans - first_hit[i] * tail) % MOD;
    }
    return (ans % MOD + MOD) % MOD;
}

int main() {
    ll n = 0;
    int c = 0;
    if (scanf("%lld %d", &n, &c) != 2) return 0;   // 输入不合法直接退出
    for (int i = 0; i < c; i++) {
        scanf("%lld %lld", &hole[i].x, &hole[i].y);
    }

    build_factorials((int)(2 * n + 1));
    int m = sort_and_unique_holes(c);
    printf("%lld\n", count_paths(n, m));
    return 0;
}
