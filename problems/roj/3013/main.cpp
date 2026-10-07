/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:13
 * update_at: 2026-10-06 11:13
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll a[MAXN]; // 商店坐标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    sort(a + 1, a + n + 1); // 排序后两端配对

    ll ans = 0;
    int pairs = n / 2; // 组数 floor(N/2)，奇数时中间元素自配对差为0
    for (int i = 1; i <= pairs; ++i) {
        ans += a[n + 1 - i] - a[i]; // 第i组：大减小
    }

    cout << ans << '\n';
    return 0;
}
