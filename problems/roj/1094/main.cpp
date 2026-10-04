/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:48
 * update_at: 2026-10-05 00:48
 */
#include <iostream>
using namespace std;

typedef long long ll;

// 判断 x 的十进制表示中是否含有数字 7
bool has_digit_seven(ll x) {
    while (x > 0) {
        if (x % 10 == 7) {
            return true;
        }
        x /= 10;
    }
    return false;
}

int main() {
    ll n;
    cin >> n;

    // 与 7 无关：既不是 7 的倍数，十进制各位也没有数字 7
    ll answer = 0;
    for (ll i = 1; i <= n; i++) {
        if (i % 7 != 0 && !has_digit_seven(i)) {
            answer += i * i;
        }
    }

    cout << answer << "\n";
    return 0;
}
