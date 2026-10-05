/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:39
 * update_at: 2026-10-06 01:39
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const ll MOD = 5000011;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;

    // s[i] 表示长度 i 的合法方案总数
    vector<ll> s(n + 1);
    s[0] = 1; // 空前缀

    for (ll i = 1; i <= n; i++) {
        ll c = s[i - 1]; // 以牝牛结尾：前 i-1 位任意合法方案
        ll b;
        if (i <= k) {
            b = 1; // 以牡牛结尾且它是第一头牡牛
        } else {
            b = s[i - k - 1]; // 上一头牡牛至少在前 i-k-1 位
        }
        s[i] = (b + c) % MOD;
    }

    cout << s[n] << "\n";
    return 0;
}
