/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:51
 * update_at: 2026-10-06 13:52
 */
#include <iostream>
#include <map>
using namespace std;

typedef long long ll;

map<ll, ll> cnt; // 值 -> 出现次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, x;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> x;
        cnt[x]++; // 哈希计数
    }

    // 按值升序输出每个不同数及其出现次数
    for (map<ll, ll>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        cout << it->first << ' ' << it->second << '\n';
    }

    return 0;
}
