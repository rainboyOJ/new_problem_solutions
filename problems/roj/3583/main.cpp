/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; if (!(cin >> n >> m)) return 0;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int cnt[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < m; i++) { int x; cin >> x; cnt[x]++; }
    static ll dp[45][45][45][45];
    static bool ok[45][45][45][45];
    ok[0][0][0][0] = true; dp[0][0][0][0] = a[0];
    for (int c1 = 0; c1 <= cnt[1]; c1++)
    for (int c2 = 0; c2 <= cnt[2]; c2++)
    for (int c3 = 0; c3 <= cnt[3]; c3++)
    for (int c4 = 0; c4 <= cnt[4]; c4++) {
        if (!ok[c1][c2][c3][c4]) continue;
        int pos = c1 + 2 * c2 + 3 * c3 + 4 * c4;
        int cs[5] = {0, c1, c2, c3, c4};
        for (int k = 1; k <= 4; k++) {
            if (cs[k] == cnt[k] || pos + k >= n) continue;
            int n1 = c1, n2 = c2, n3 = c3, n4 = c4;
            if (k == 1) n1++; else if (k == 2) n2++; else if (k == 3) n3++; else n4++;
            ll gain = dp[c1][c2][c3][c4] + a[pos + k];
            if (!ok[n1][n2][n3][n4] || gain > dp[n1][n2][n3][n4]) {
                ok[n1][n2][n3][n4] = true; dp[n1][n2][n3][n4] = gain;
            }
        }
    }
    cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]] << '\n';
    return 0;
}
