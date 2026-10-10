/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:41
 * update_at: 2026-10-08 22:41
 */
#include <iostream>

using namespace std;

typedef long long ll;

// 判断 x 是否为素数：1 既不是素数也不是合数，x < 2 直接排除；
// 只需试除到 sqrt(x)，用 i * i <= x 作上界可避免浮点开方的精度问题。
bool is_prime(ll x) {
    if (x < 2) return false;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// 逐行输出 [a, b] 内的素数；区间内一个素数都没有时自然不输出任何字节。
void solve() {
    ll a, b;
    if (!(cin >> a >> b)) return;
    for (ll i = a; i <= b; i++) {
        if (is_prime(i)) {
            cout << i << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
