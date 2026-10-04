/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:11
 * update_at: 2026-10-05 05:11
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;          // 巧克力总数
ll a = 1, b = 1; // a=f[i-2], b=f[i-1]，初始 f[0]=f[1]=1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 滚动递推：f[i] = f[i-1] + f[i-2]
    for (ll i = 2; i <= n; i++) {
        ll c = a + b; // c 为 f[i]
        a = b;
        b = c;
    }

    cout << b << "\n";
    return 0;
}
