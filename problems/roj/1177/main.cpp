/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:25
 * update_at: 2026-10-05 04:25
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 505; // 序列最大长度

ll a[MAXN];      // 原序列
ll odd[MAXN];    // 筛选出的奇数
ll n, k;         // n 为长度，k 为奇数个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] & 1) { // 二进制最低位为 1，表示奇数
            odd[++k] = a[i];
        }
    }

    sort(odd + 1, odd + k + 1); // 对奇数升序排序

    for (ll i = 1; i <= k; i++) {
        if (i > 1) cout << ',';
        cout << odd[i];
    }
    cout << '\n';

    return 0;
}
