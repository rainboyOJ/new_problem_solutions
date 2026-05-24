/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-05 16:08:25
 * oj: 51Node-1256
 * title: 乘法逆元
 * description: 乘法逆元入门题目
 */
#include <iostream>

using namespace std;

typedef long long ll;

ll n, m;

// 求解 ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    // 递归反着传 (y, x)
    ll d = exgcd(b, a % b, y, x);
    
    // 回来减乘除 (y -= a/b*x)
    y -= a / b * x;
    
    return d;
}

// 求 a 在模 mod 下的逆元
ll inv(ll a, ll mod) {
    ll x, y;
    // 【安全检查】如果 a 和 mod 不互质，其实没有逆元
    // 但题目保证了互质，所以可以直接解
    exgcd(a, mod, x, y);
    
    // 【核心】防负数处理
    return (x % mod + mod) % mod;
}

int main() {
    // 关闭流同步，加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 题目输入是 M, N
    // 我们求 K * M % N = 1，即 M 关于 N 的逆元
    if (cin >> m >> n) {
        cout << inv(m, n) << endl;
    }
    
    return 0;
}