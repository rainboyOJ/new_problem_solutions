/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:09
 * update_at: 2026-10-06 10:09
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll n;
ll a[MAXN];      // a[1..n] 保存序列
ll g[MAXN][MAXN]; // g[l][r] 表示剩余区间为 [l, r]、轮到当前行动者时，其最终得分减对手得分的最大差值
ll total;

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        total += a[i];
    }
}

void solve() {
    // 按区间长度从小到大填表；g[l][r] 由 g[l+1][r] 与 g[l][r-1] 推出
    for (ll len = 1; len <= n; len++) {
        for (ll l = 1; l + len - 1 <= n; l++) {
            ll r = l + len - 1;
            // 取左端就入 a[l]，对手成为 [l+1, r] 的行动者净胜 g[l+1][r]，故本选择净胜 a[l] - g[l+1][r]；取右端同理
            g[l][r] = max(a[l] - g[l + 1][r], a[r] - g[l][r - 1]);
        }
    }
    ll diff = g[1][n];
    // 两人得分之和恒为 total，先手减后手为 diff，解这个二元一次方程组
    cout << (total + diff) / 2 << " " << (total - diff) / 2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
