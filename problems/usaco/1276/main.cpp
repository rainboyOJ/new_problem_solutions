/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:05
 * update_at: 2026-07-11 17:06
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXM = 15;
const int MAXS = 100;
const int INF = 1e9;

int n, m;
int need[MAXS + 5]; // need[x] 表示第 x 个牛棚需要降温多少

int a[MAXM], b[MAXM], p[MAXM], cost[MAXM];

bool check(int mask, int &total_cost) {
    int cool[MAXS + 5];
    memset(cool, 0, sizeof(cool));
    total_cost = 0;

    for (int i = 0; i < m; i++) {
        if ((mask & (1 << i)) == 0) {
            continue;
        }
        total_cost += cost[i];
        for (int x = a[i]; x <= b[i]; x++) {
            cool[x] += p[i];
        }
    }

    for (int x = 1; x <= MAXS; x++) {
        if (cool[x] < need[x]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int s, t, c;
        cin >> s >> t >> c;
        for (int x = s; x <= t; x++) {
            need[x] = c;
        }
    }

    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> p[i] >> cost[i];
    }

    int ans = INF;
    for (int mask = 0; mask < (1 << m); mask++) {
        int total_cost = 0;
        if (check(mask, total_cost) && total_cost < ans) {
            ans = total_cost;
        }
    }

    cout << ans << '\n';

    return 0;
}
