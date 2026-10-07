/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:56
 * update_at: 2026-10-05 23:56
 */

// 题意：佛祖手掌是长为 n 的圆圈，大圣每次逆时针飞 d，问从 x 到 y 最少翻几个筋斗。
// 思路：跳 k 次后位置是 (x + k*d) mod n，解线性同余方程 k*d ≡ y-x (mod n)。
//       设 g = gcd(d, n)：g 不整除 (y-x) 时无解；否则两边除以 g，在模 m = n/g 下
//       用扩展欧几里得求 (d/g) 的逆元，得到最小非负解 k0，即答案。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n, d, x, y; // 每组询问的手掌长度 n、每次飞行距离 d、起点 x、终点 y

// 辗转相除求最大公约数
ll mygcd(ll a, ll b) {
    while (b != 0) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// 扩展欧几里得：求 gcd(a, b)，并求出 a*x + b*y = gcd 的一组整数解
ll exgcd(ll a, ll b, ll &px, ll &py) {
    if (b == 0) {
        px = 1;
        py = 0;
        return a;
    }
    ll gx = 0, gy = 0;
    ll g = exgcd(b, a % b, gx, gy); // 先解子问题 b*x + (a%b)*y = g
    px = gy;                        // 回代：a%b = a - (a/b)*b
    py = gx - (a / b) * gy;
    return g;
}

// 解方程 k*d ≡ y-x (mod n)，返回最小非负解；无解返回 -1
ll solve_query() {
    ll g = mygcd(d, n);
    ll diff = ((y - x) % n + n) % n; // 差值先调成非负，方便整除判定
    if (diff % g != 0) {
        return -1; // g 不整除差值，永远到不了 y
    }
    ll m = n / g; // 约简后的模数，也是解的周期
    ll p = 0, q = 0;
    exgcd(d / g, m, p, q);          // 此时 gcd(d/g, m) = 1，逆元存在
    ll inv = ((p % m) + m) % m;     // 把逆元调成 [0, m) 内的最小非负剩余
    ll k = (diff / g % m) * inv % m; // 乘上逆元取模，k0 就是最少跳跃次数
    return k;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) {
        return 0;
    }
    while (T--) {
        scanf("%lld %lld %lld %lld", &n, &d, &x, &y);
        ll ans = solve_query();
        if (ans == -1) {
            printf("Impossible\n");
        } else {
            printf("%lld\n", ans);
        }
    }
    return 0;
}
