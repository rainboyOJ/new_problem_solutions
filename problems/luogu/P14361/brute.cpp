/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:53
 * update_at: 2026-10-01 22:53
 */
// brute.cpp：小数据暴力解，递归枚举每个人分到哪个部门，用来帮助理解题意并辅助对拍。
// 只适合 n ≤ 10 的对拍场景。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

ll n, limit_num;
int a[MAXN][4]; // a[i][j] = 第 i 个人对第 j 个部门的满意度
int cnt[4];     // 各部门当前人数
ll best_ans;

// dfs(pos, sum)：已分配前 pos-1 个人，当前满意度为 sum，继续分配第 pos 个人。
void dfs(ll pos, ll sum) {
    if (pos > n) {
        best_ans = max(best_ans, sum);
        return;
    }

    for (int dep = 1; dep <= 3; dep++) {
        if (cnt[dep] == limit_num) {
            continue;
        }
        cnt[dep]++;
        dfs(pos + 1, sum + a[pos][dep]);
        cnt[dep]--;
    }
}

void solve_case() {
    cin >> n;
    limit_num = n / 2;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i][1] >> a[i][2] >> a[i][3];
    }

    cnt[1] = cnt[2] = cnt[3] = 0;
    best_ans = -1;
    dfs(1, 0);
    cout << best_ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
