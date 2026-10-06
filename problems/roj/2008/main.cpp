/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:25
 * update_at: 2026-10-06 09:25
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, s;

// 判断 x 在 base 进制下是否为回文
bool is_palindrome(ll x, ll base) {
    ll digits[64]; // 低位在前保存各进制数码
    ll len = 0;
    while (x > 0) {
        digits[len++] = x % base;
        x /= base;
    }
    for (ll i = 0; i < len / 2; i++) {
        if (digits[i] != digits[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 统计 x 在 2~10 进制中回文的进制个数
ll count_palindrome(ll x) {
    ll cnt = 0;
    for (ll base = 2; base <= 10; base++) {
        if (is_palindrome(x, base)) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s;
    ll found = 0;
    ll x = s + 1;
    while (found < n) {
        if (count_palindrome(x) >= 2) {
            cout << x << "\n";
            found++;
        }
        x++;
    }
    return 0;
}
