/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:07
 * update_at: 2026-07-11 18:09
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;
ll p[MAXN], t[MAXN], d[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    d[0] = 0;
    d[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        d[i] = p[i] - t[i];
    }

    ll sum = 0;
    for (int i = 0; i <= n; i++) {
        sum += llabs(d[i + 1] - d[i]);
    }

    cout << sum / 2 << '\n';

    return 0;
}
