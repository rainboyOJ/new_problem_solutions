/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 16:38
 * update_at: 2026-10-23 16:38
 */
// main.cpp：线扫一遍，每行只保留「停在线段左端点 / 右端点」两个状态
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 20005;

ll n;
ll L[MAXN], R[MAXN];

// dp_left[i]：走完第 1..i 行的线段，最后停在第 i 行线段的左端点 L[i] 时的最短路程
// dp_right[i]：同上，最后停在第 i 行线段的右端点 R[i]
ll dp_left[MAXN], dp_right[MAXN];

ll abs_dist(ll a, ll b) {
    if (a > b) {
        return a - b;
    }
    return b - a;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }
}

void solve() {
    // 第 1 行从 (1,1) 出发。
    // 想停到 L[1]：先走到 R[1] 再折回 L[1]；想停到 R[1]：直接走到 L[1] 再一路往右。
    ll len1 = R[1] - L[1];
    dp_left[1] = abs_dist(1, R[1]) + len1;
    dp_right[1] = abs_dist(1, L[1]) + len1;

    for (ll i = 2; i <= n; i++) {
        ll len = R[i] - L[i];

        // 上一行无论停在哪，都要先竖直向下走到本行的同一列（代价 1），
        // 然后在本行从这一列出发，覆盖 L[i] 与 R[i]，最后停到目标端点。
        // 停到 L[i]：必须先到 R[i] 再折回，水平代价 = |入口列 - R[i]| + len
        dp_left[i] = min(dp_left[i - 1] + abs_dist(L[i - 1], R[i]),
                         dp_right[i - 1] + abs_dist(R[i - 1], R[i]))
                    + len + 1;

        // 停到 R[i]：必须先到 L[i] 再一路往右，水平代价 = |入口列 - L[i]| + len
        dp_right[i] = min(dp_left[i - 1] + abs_dist(L[i - 1], L[i]),
                          dp_right[i - 1] + abs_dist(R[i - 1], L[i]))
                     + len + 1;
    }

    // 最后还要从第 n 行的停靠点走到 (n,n)，只差水平距离
    ll answer = min(dp_left[n] + abs_dist(L[n], n), dp_right[n] + abs_dist(R[n], n));
    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
