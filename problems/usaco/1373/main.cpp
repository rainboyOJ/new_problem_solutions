/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:11
 * update_at: 2026-07-11 16:12
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
long long a[MAXN];
long long diff1[MAXN];
long long diff2[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        diff1[i] = a[i] - a[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        diff2[i] = diff1[i] - diff1[i - 1];
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += llabs(diff2[i]);
    }

    cout << ans << '\n';

    return 0;
}
