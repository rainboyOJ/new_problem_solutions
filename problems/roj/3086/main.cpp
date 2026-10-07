/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:10
 * update_at: 2026-10-06 18:10
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

typedef long long ll;

int n;
bool is_prime[MAXN]; // is_prime[i] = true 表示 i 是质数

// 埃氏筛：筛出 2 ~ n 的全部质数
void sieve(int limit) {
    for (int i = 2; i <= limit; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; (ll)i * i <= limit; i++) {
        if (is_prime[i]) {
            // 从 i*i 开始把 i 的倍数划掉
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

// 勒让德公式：计算 n! 中质数 p 的指数
// c_p = n/p + n/p^2 + n/p^3 + ...
ll legendre(int p, int nn) {
    ll power = nn;
    ll cnt = 0;
    while (power) {
        power /= p;
        cnt += power;
    }
    return cnt;
}

void solve() {
    cin >> n;

    // n = 1 时 1! = 1，没有质因子，输出为空
    if (n < 2) {
        return;
    }

    sieve(n);

    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            cout << p << " " << legendre(p, n) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
