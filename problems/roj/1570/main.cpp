/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:11
 * update_at: 2026-10-05 09:11
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 205; // 2n 最大为 200，留少量余量

ll n;
ll head[MAXN];     // 倍长后的头标记序列 head[1..2n]，满足 head[i+n] = head[i]
ll dp[MAXN][MAXN]; // dp[l][r] 表示把珠子区间 [l,r] 合并成一颗珠子释放的最大总能量

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> head[i];
    }
    // 破环成链：倍长序列后，环上任意连续 n 颗珠子都对应一个长度 n 的区间
    for (ll i = 1; i <= n; i++) {
        head[i + n] = head[i];
    }
}

void solve() {
    // 按区间长度从小到大递推，保证子区间先算好
    for (ll len = 2; len <= n; len++) {
        for (ll l = 1; l + len - 1 <= 2 * n - 1; l++) {
            ll r = l + len - 1;
            // 枚举最后一次合并的分割点 k：左半段 [l,k] 与右半段 [k+1,r] 先各自合并
            // 左半段合并后的珠子为 (head[l], head[k+1])，右半段为 (head[k+1], head[r+1])
            for (ll k = l; k < r; k++) {
                ll energy = dp[l][k] + dp[k + 1][r] + head[l] * head[k + 1] * head[r + 1];
                if (energy > dp[l][r]) {
                    dp[l][r] = energy;
                }
            }
        }
    }

    // 枚举环的断开位置，取所有长度为 n 的区间中的最大值
    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (dp[i][i + n - 1] > ans) {
            ans = dp[i][i + n - 1];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
