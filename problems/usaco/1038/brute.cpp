/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:22
 * update_at: 2026-07-11 20:23
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个可用位置选或不选。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXP = 35;

int n, m;
int tot;
ll pos[MAXP];      // 所有有草的整数位置，仅用于小数据
int choose_pos[MAXP]; // choose_pos[i] 表示第 i 个位置是否放牛
ll ans;

void check_answer() {
    int cnt = 0;
    ll last = -1;
    ll mindist = (ll)4e18;

    for (int i = 1; i <= tot; i++) {
        if (choose_pos[i] == 1) {
            cnt++;
            if (last != -1) {
                mindist = min(mindist, pos[i] - last);
            }
            last = pos[i];
        }
    }

    if (cnt == n) {
        ans = max(ans, mindist);
    }
}

void dfs(int dep) {
    if (dep == tot + 1) {
        check_answer();
        return;
    }

    choose_pos[dep] = 0;
    dfs(dep + 1);

    choose_pos[dep] = 1;
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        ll l, r;
        cin >> l >> r;
        for (ll x = l; x <= r && tot + 1 < MAXP; x++) {
            tot++;
            pos[tot] = x;
        }
    }

    sort(pos + 1, pos + tot + 1);
    dfs(1);
    cout << ans << '\n';

    return 0;
}
