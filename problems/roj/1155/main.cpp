/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:45
 * update_at: 2026-10-05 03:45
 */
// 三位回文素数：按 aba = 101a + 10b 直接生成 90 个回文候选，再试除判素数
#include <iostream>
using namespace std;

typedef long long ll;

// 试除法判断素数：只需试除到 floor(sqrt(n))，写成 d*d <= n 避免开方的浮点误差
bool is_prime(ll n) {
    if (n < 2) {
        return false;
    }
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 三位回文数形如 aba：a 是百位/个位取 1..9，b 是十位取 0..9，共 90 个候选
    for (ll a = 1; a <= 9; a++) {
        for (ll b = 0; b <= 9; b++) {
            ll x = 101 * a + 10 * b;
            if (is_prime(x)) {
                cout << x << "\n";
            }
        }
    }
    return 0;
}
