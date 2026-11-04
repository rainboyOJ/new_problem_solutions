/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-03 10:15
 * update_at: 2026-11-04 19:55
 */
// brute.cpp：先求前缀和，再枚举所有 l,r，用 p[r] - p[l-1] 与长度比较，O(n^2)。
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 2e6+5;
int n;
string s;
int p[maxn];            // p[i] = a[1] + ... + a[i]

void sol(){
    cin >> n >> s;

    p[0] = 0;
    for (int i = 1; i <= n; i++)
        p[i] = p[i-1] + (s[i-1] - '0');

    ll ans = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            if (p[r] - p[l-1] == r - l + 1)     // 子段和 == 子段长度
                ans++;
        }
    }
    cout << ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        sol();
    return 0;
}
