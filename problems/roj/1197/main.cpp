/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:23
 * update_at: 2026-10-04 23:23
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 505;
const int MAXN = 505;
const ll INF = 1e18; // “尚未转移”的哨兵，远大于所有距离和的上界

ll m, n;
ll pos[MAXM];          // pos[i]：第 i 个村到第 1 个村的距离（前缀和）
ll cost[MAXM][MAXM];   // cost[l][r]：村 l..r 共用一所小学（建在中位村）时，段内的距离和
ll dp[MAXN][MAXM];     // dp[j][i]：前 i 个村恰好建 j 所小学的最小距离和

// 预处理每一段的代价：段内小学建在中位村 (l+r)/2 处，逐村累加距离。
void build_cost() {
    for (ll l = 1; l <= m; l++) {
        for (ll r = l; r <= m; r++) {
            ll mid = (l + r) / 2; // 村庄编号与坐标同序，中位村就是编号中位
            ll sum = 0;
            for (ll v = l; v <= r; v++) {
                sum += llabs(pos[v] - pos[mid]);
            }
            cost[l][r] = sum;
        }
    }
}

void solve() {
    build_cost();

    // 只建 1 所小学时，前 i 个村全归这一所学校负责。
    for (ll i = 1; i <= m; i++) {
        dp[1][i] = cost[1][i];
    }
    // 转移：枚举最后一所学校负责的段 [k+1, i]；k 从 j-1 起保证前面每所至少管一个村。
    for (ll j = 2; j <= n; j++) {
        for (ll i = j; i <= m; i++) {
            ll best = INF;
            for (ll k = j - 1; k <= i - 1; k++) {
                ll cur = dp[j - 1][k] + cost[k + 1][i];
                if (cur < best) {
                    best = cur;
                }
            }
            dp[j][i] = best;
        }
    }

    cout << dp[n][m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    pos[1] = 0;
    for (ll i = 2; i <= m; i++) {
        ll d;
        cin >> d;
        pos[i] = pos[i - 1] + d;
    }

    solve();

    return 0;
}
