/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:48
 * update_at: 2026-07-11 16:49
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long k;
long long day_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> day_arr[i];
    }

    long long ans = k + 1;
    for (int i = 2; i <= n; i++) {
        long long keep_cost = day_arr[i] - day_arr[i - 1];
        long long restart_cost = k + 1;
        ans += min(keep_cost, restart_cost);
    }

    cout << ans << '\n';

    return 0;
}
