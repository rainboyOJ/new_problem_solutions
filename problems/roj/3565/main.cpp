/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:04
 * update_at: 2026-10-06 14:04
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

int cnt[26]; // cnt[i] 表示字母 ('a' + i) 在单词中出现的次数

// 判断 x 是否为质数，x 为 0 或 1 时直接返回 false
bool is_prime(ll x) {
    if (x < 2) {
        return false;
    }
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    string word;
    cin >> word;

    // 统计每个字母出现的次数
    ll len = word.size();
    for (ll i = 0; i < len; i++) {
        cnt[word[i] - 'a']++;
    }

    // maxn 与 minn 都只在出现过的字母之间比较
    ll maxn = 0;
    ll minn = -1;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) {
            if (cnt[i] > maxn) {
                maxn = cnt[i];
            }
            if (minn == -1 || cnt[i] < minn) {
                minn = cnt[i];
            }
        }
    }

    ll diff = maxn - minn;
    if (is_prime(diff)) {
        cout << "Lucky Word" << "\n";
        cout << diff << "\n";
    } else {
        cout << "No Answer" << "\n";
        cout << 0 << "\n";
    }

    return 0;
}
