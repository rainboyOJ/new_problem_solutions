/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:29
 * update_at: 2026-10-06 01:29
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 55;

ll a[MAXN]; // a[i] 表示第 i 堆石子的数量

// 判断当前局面是否先手必败。
// k1/k2 为大小为 1/2 的堆数，n 为堆数，s 为石子总数，maxv 为最大堆。
bool is_losing(ll k1, ll k2, ll n, ll s, ll maxv) {
    if (maxv > 2) {
        // 存在大于 2 的堆：必败 ⇔ k1 为偶数 且 (s+n) 为奇数。
        return k1 % 2 == 0 && (s + n) % 2 == 1;
    }
    // 只有大小为 1、2 的堆：k2<=1 时看 k1 对 3 取模；
    // k2 为奇数(>=3) 时看 k1 奇偶；k2 为偶数(>=2) 时先手必胜。
    if (k2 < 2) {
        return k1 % 3 == 0;
    }
    if (k2 % 2 == 1) {
        return k1 % 2 == 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        ll k1 = 0;   // 大小为 1 的堆数
        ll k2 = 0;   // 大小为 2 的堆数
        ll s = 0;    // 石子总数
        ll maxv = 0; // 最大堆的大小
        for (ll i = 1; i <= n; i++) {
            cin >> a[i];
            s += a[i];
            if (a[i] == 1) k1++;
            if (a[i] == 2) k2++;
            if (a[i] > maxv) maxv = a[i];
        }
        // 先手必败输出 NO，否则输出 YES（Alice 先手）。
        if (is_losing(k1, k2, n, s, maxv)) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}
